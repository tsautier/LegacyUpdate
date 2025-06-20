#include "stdafx.h"
#include "NGen.h"
#include "Exec.h"
#include "VersionInfo.h"
#include "Wow64.h"
#include <Shlwapi.h>

STDMETHODIMP PauseResumeNGenQueue(BOOL state) {
	// Pause and resume .NET Framework global assembly cache (GAC) and NGen queue
	static LPWSTR versions[] = {
		L"v4.0.30319",
		L"v2.0.50727"
	};

	SYSTEM_INFO systemInfo;
	OurGetNativeSystemInfo(&systemInfo);
	BOOL hasFramework64 = systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64;

	HRESULT hr = S_OK;

	for (int i = 0; i < ARRAYSIZE(versions); i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 1 && !hasFramework64) {
				break;
			}

			WCHAR path[MAX_PATH];
			wsprintf(path, L"%%SystemRoot%%\\Microsoft.NET\\Framework%ls\\%ls\\ngen.exe", j == 1 ? L"64": L"", versions[i]);
			ExpandEnvironmentStrings(path, path, ARRAYSIZE(path));

			if (PathFileExists(path)) {
				hr = Exec(NULL, path, state ? L"queue pause" : L"queue continue", NULL, SW_HIDE, TRUE, NULL);

				if (SUCCEEDED(hr) && state) {
					// Execute queue in the background
					hr = Exec(NULL, path, L"executeQueuedItems", NULL, SW_HIDE, FALSE, NULL);
				}

				if (SUCCEEDED(hr)) {
					break;
				}
			}
		}
	}

	if (AtLeastWin8() && state) {
		// Fire the scheduled tasks
		static LPWSTR ngenTask = L"\\Microsoft\\Windows\\.NET Framework\\.NET Framework NGEN v4.0.30319";

		for (int i = 0; i < 2; i++) {
			if (i == 1 && !hasFramework64) {
				break;
			}

			WCHAR path[MAX_PATH], args[MAX_PATH];
			ExpandEnvironmentStrings(L"%SystemRoot%\\System32\\schtasks.exe", path, ARRAYSIZE(path));
			wsprintf(args, L"/run /tn \"%ls%ls\" /hresult", ngenTask, i == 1 ? L" 64": L"");
			hr = Exec(NULL, path, args, NULL, SW_HIDE, TRUE, NULL);
		}
	}

	return hr;
}
