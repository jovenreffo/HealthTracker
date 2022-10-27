#pragma once
#include <wx/stdpaths.h>
#include <wx/log.h>

class StandardPath: protected wxStandardPaths
{
public:
	__forceinline wxString GetExecPath() const { return GetExecutablePath(); }
	__forceinline wxString GetDataDire() const { return GetLocalDataDir(); }
	__forceinline wxString GetDocumentsDire() const { return GetDocumentsDir(); }
};

namespace path_data
{
	static StandardPath path;
	static const wxString execPath = path.GetExecPath();
	static const wxString dataDir = path.GetDataDire();
	static const wxString documentsDir = path.GetDocumentsDire();
}