#include "pch-il2cpp.h"

#include "VersionControl.h"

#include <Windows.h>
#include <iostream>
#include <wininet.h>

#include "json.hpp"

#pragma comment(lib, "wininet.lib")

using json = nlohmann::json;

VersionControl::VersionControl(const char* version_tag, const wchar_t* url)
{
	current_version_tag = version_tag;
    requestUrl = url;
    isUpToDate = false;
    latestDownloadLink = nullptr;
}

const char* VersionControl::GetCurrentVersionTag()
{
	return current_version_tag;
}

bool VersionControl::IsUpToDate()
{
    return isUpToDate;
}

const char* VersionControl::GetLatestDownloadLink()
{
    return latestDownloadLink;
}

void VersionControl::SetIsUpToDate(bool value)
{
    isUpToDate = value;
}

void VersionControl::CheckForUpdate()
{
    HINTERNET hInternet = InternetOpen(L"DevourClient_Version_Control", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

    if (hInternet) {
        HINTERNET hConnect = InternetOpenUrl(hInternet, requestUrl, NULL, 0, INTERNET_FLAG_RELOAD, 0);

        if (hConnect) {
            std::vector<char> buffer(4096);
            DWORD bytesRead;
            std::string responseData;

            while (InternetReadFile(hConnect, &buffer[0], buffer.size(), &bytesRead) && bytesRead > 0) {
                responseData.append(&buffer[0], bytesRead);
            }

            json data = json::parse(responseData);

            if (data.find("tag_name") != data.end() && data["tag_name"].is_string()) {
                std::string latestTagName = data["tag_name"];

                if (strcmp(latestTagName.c_str(), current_version_tag) == 0) {
                    SetIsUpToDate(true);
                }
                else {
                    SetIsUpToDate(false);
                }
            }

            if (data.find("assets") != data.end() && data["assets"].is_array() && !data["assets"].empty()) {
                if (data["assets"][0].find("browser_download_url") != data["assets"][0].end() && data["assets"][0]["browser_download_url"].is_string()) {
                    std::string downloadUrl = data["assets"][0]["browser_download_url"];
                    latestDownloadLink = _strdup(downloadUrl.c_str());
                }
            }

            InternetCloseHandle(hConnect);
        }
        else {
            std::cout << "[DevourClient]: URL opening error! Skipping update check..." << std::endl;
        }
        
    }
    else {
        std::cout << "[DevourClient]: Unable to establish an internet connection! Skipping update check..." << std::endl;
    }
}

VersionControl::~VersionControl()
{
    current_version_tag = nullptr;
    requestUrl = nullptr;
}