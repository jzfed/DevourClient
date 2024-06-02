#pragma once

class VersionControl {
public:
	VersionControl(const char* version_tag, const wchar_t* url);
	~VersionControl();

	const char* GetCurrentVersionTag();
	void CheckForUpdate();
	bool IsUpToDate();
	const char* GetLatestDownloadLink();
private:
	const char* latestDownloadLink;
	bool isUpToDate;
	const char* current_version_tag;
	const wchar_t* requestUrl;
private:
	void SetIsUpToDate(bool value);
};