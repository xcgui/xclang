/*
				GNU GENERAL PUBLIC LICENSE
				   Version 2, June 1991
COPYRIGHT (C) Bestkakkoii 2023 All Rights Reserved.
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/

#pragma once

//@模块名称  CXFTP
//@版本  1.0.0
//@日期  2023-12-10
//@作者  Bestkakkoii (QQ: 1642687802)
//@模块备注 封装自微软wininet.h
//@依赖  module_base.h

#include <windows.h> 
#include <wininet.h>
#include <string>
#include <vector>

//@分组{ CXFTP
/*
typedef void (__stdcall* INTERNET_STATUS_CALLBACK)(
    _In_ HINTERNET hInternet,
    _In_opt_ DWORD_PTR dwContext,
    _In_ DWORD dwInternetStatus,
    _In_opt_ LPVOID lpvStatusInformation,
    _In_ DWORD dwStatusInformationLength
    );

typedef INTERNET_STATUS_CALLBACK * LPINTERNET_STATUS_CALLBACK;
*/

#pragma comment(lib, "wininet.lib")

class CXFTP
{
public:
	// 用于表示文件传输的类型
	enum TransferType
	{
		Binary = FTP_TRANSFER_TYPE_BINARY, // 二进制传输模式，适用于非文本文件
		Ascii = FTP_TRANSFER_TYPE_ASCII    // ASCII传输模式，适用于文本文件
	};

	// 设置与缓存相关的标志
	enum CacheSettings
	{
		Reload = INTERNET_FLAG_RELOAD,           // 强制从服务器重新下载请求的文件
		Resynchronize = INTERNET_FLAG_RESYNCHRONIZE, // 与Reload类似，但首先检查本地缓存
		Hyperlink = INTERNET_FLAG_HYPERLINK,     // 为超链接操作预留，当前未使用
		NeedFile = INTERNET_FLAG_NEED_FILE       // 如果本地缓存不可用，则从服务器获取文件
	};

    enum NetOption
    {
        callback = INTERNET_OPTION_CALLBACK,
        connect_timeout = INTERNET_OPTION_CONNECT_TIMEOUT,
        connect_retries = INTERNET_OPTION_CONNECT_RETRIES,
        connect_backoff = INTERNET_OPTION_CONNECT_BACKOFF,
        send_timeout = INTERNET_OPTION_SEND_TIMEOUT,
        control_send_timeout = INTERNET_OPTION_CONTROL_SEND_TIMEOUT,
        receive_timeout = INTERNET_OPTION_RECEIVE_TIMEOUT,
        control_receive_timeout = INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT,
        data_send_timeout = INTERNET_OPTION_DATA_SEND_TIMEOUT,
        data_receive_timeout = INTERNET_OPTION_DATA_RECEIVE_TIMEOUT,
        handle_type = INTERNET_OPTION_HANDLE_TYPE,
        listen_timeout = INTERNET_OPTION_LISTEN_TIMEOUT,
        read_buffer_size = INTERNET_OPTION_READ_BUFFER_SIZE,
        write_buffer_size = INTERNET_OPTION_WRITE_BUFFER_SIZE,
        async_id = INTERNET_OPTION_ASYNC_ID,
        async_priority = INTERNET_OPTION_ASYNC_PRIORITY,
        parent_handle = INTERNET_OPTION_PARENT_HANDLE,
        keep_connection = INTERNET_OPTION_KEEP_CONNECTION,
        request_flags = INTERNET_OPTION_REQUEST_FLAGS,
        extended_error = INTERNET_OPTION_EXTENDED_ERROR,
        offline_mode = INTERNET_OPTION_OFFLINE_MODE,
        cache_stream_handle = INTERNET_OPTION_CACHE_STREAM_HANDLE,
        username = INTERNET_OPTION_USERNAME,
        password = INTERNET_OPTION_PASSWORD,
        async = INTERNET_OPTION_ASYNC,
        security_flags = INTERNET_OPTION_SECURITY_FLAGS,
        security_certificate_struct = INTERNET_OPTION_SECURITY_CERTIFICATE_STRUCT,
        datafile_name = INTERNET_OPTION_DATAFILE_NAME,
        url = INTERNET_OPTION_URL,
        security_certificate = INTERNET_OPTION_SECURITY_CERTIFICATE,
        security_key_bitness = INTERNET_OPTION_SECURITY_KEY_BITNESS,
        refresh = INTERNET_OPTION_REFRESH,
        proxy = INTERNET_OPTION_PROXY,
        settings_changed = INTERNET_OPTION_SETTINGS_CHANGED,
        version = INTERNET_OPTION_VERSION,
        user_agent = INTERNET_OPTION_USER_AGENT,
        end_browser_session = INTERNET_OPTION_END_BROWSER_SESSION,
        proxy_username = INTERNET_OPTION_PROXY_USERNAME,
        proxy_password = INTERNET_OPTION_PROXY_PASSWORD,
        context_value = INTERNET_OPTION_CONTEXT_VALUE,
        connect_limit = INTERNET_OPTION_CONNECT_LIMIT,
        security_select_client_cert = INTERNET_OPTION_SECURITY_SELECT_CLIENT_CERT,
        policy = INTERNET_OPTION_POLICY,
        disconnected_timeout = INTERNET_OPTION_DISCONNECTED_TIMEOUT,
        connected_state = INTERNET_OPTION_CONNECTED_STATE,
        idle_state = INTERNET_OPTION_IDLE_STATE,
        offline_semantics = INTERNET_OPTION_OFFLINE_SEMANTICS,
        secondary_cache_key = INTERNET_OPTION_SECONDARY_CACHE_KEY,
        callback_filter = INTERNET_OPTION_CALLBACK_FILTER,
        connect_time = INTERNET_OPTION_CONNECT_TIME,
        send_throughput = INTERNET_OPTION_SEND_THROUGHPUT,
        receive_throughput = INTERNET_OPTION_RECEIVE_THROUGHPUT,
        request_priority = INTERNET_OPTION_REQUEST_PRIORITY,
        http_version = INTERNET_OPTION_HTTP_VERSION,
        reset_urlcache_session = INTERNET_OPTION_RESET_URLCACHE_SESSION,
        error_mask = INTERNET_OPTION_ERROR_MASK,
        from_cache_timeout = INTERNET_OPTION_FROM_CACHE_TIMEOUT,
        bypass_edited_entry = INTERNET_OPTION_BYPASS_EDITED_ENTRY,
        http_decoding = INTERNET_OPTION_HTTP_DECODING,
        diagnostic_socket_info = INTERNET_OPTION_DIAGNOSTIC_SOCKET_INFO,
        codepage = INTERNET_OPTION_CODEPAGE,
        cache_timestamps = INTERNET_OPTION_CACHE_TIMESTAMPS,
        disable_autodial = INTERNET_OPTION_DISABLE_AUTODIAL,
        max_conns_per_server = INTERNET_OPTION_MAX_CONNS_PER_SERVER,
        max_conns_per_1_0_server = INTERNET_OPTION_MAX_CONNS_PER_1_0_SERVER,
        per_connection_option = INTERNET_OPTION_PER_CONNECTION_OPTION,
        digest_auth_unload = INTERNET_OPTION_DIGEST_AUTH_UNLOAD,
        ignore_offline = INTERNET_OPTION_IGNORE_OFFLINE,
        identity = INTERNET_OPTION_IDENTITY,
        remove_identity = INTERNET_OPTION_REMOVE_IDENTITY,
        alter_identity = INTERNET_OPTION_ALTER_IDENTITY,
        suppress_behavior = INTERNET_OPTION_SUPPRESS_BEHAVIOR,
        autodial_mode = INTERNET_OPTION_AUTODIAL_MODE,
        autodial_connection = INTERNET_OPTION_AUTODIAL_CONNECTION,
        client_cert_context = INTERNET_OPTION_CLIENT_CERT_CONTEXT,
        auth_flags = INTERNET_OPTION_AUTH_FLAGS,
        cookies_3rd_party = INTERNET_OPTION_COOKIES_3RD_PARTY,
        disable_passport_auth = INTERNET_OPTION_DISABLE_PASSPORT_AUTH,
        send_utf8_servername_to_proxy = INTERNET_OPTION_SEND_UTF8_SERVERNAME_TO_PROXY,
        exempt_connection_limit = INTERNET_OPTION_EXEMPT_CONNECTION_LIMIT,
        enable_passport_auth = INTERNET_OPTION_ENABLE_PASSPORT_AUTH,
        hibernate_inactive_worker_threads = INTERNET_OPTION_HIBERNATE_INACTIVE_WORKER_THREADS,
        activate_worker_threads = INTERNET_OPTION_ACTIVATE_WORKER_THREADS,
        restore_worker_thread_defaults = INTERNET_OPTION_RESTORE_WORKER_THREAD_DEFAULTS,
        socket_send_buffer_length = INTERNET_OPTION_SOCKET_SEND_BUFFER_LENGTH,
        proxy_settings_changed = INTERNET_OPTION_PROXY_SETTINGS_CHANGED,
        datafile_ext = INTERNET_OPTION_DATAFILE_EXT,
        codepage_path = INTERNET_OPTION_CODEPAGE_PATH,
        codepage_extra = INTERNET_OPTION_CODEPAGE_EXTRA,
        idn = INTERNET_OPTION_IDN,
        max_conns_per_proxy = INTERNET_OPTION_MAX_CONNS_PER_PROXY,
        suppress_server_auth = INTERNET_OPTION_SUPPRESS_SERVER_AUTH,
        server_cert_chain_context = INTERNET_OPTION_SERVER_CERT_CHAIN_CONTEXT,
        enable_redirect_cache_read = INTERNET_OPTION_ENABLE_REDIRECT_CACHE_READ,
        compressed_content_length = INTERNET_OPTION_COMPRESSED_CONTENT_LENGTH,
        enable_http_protocol = INTERNET_OPTION_ENABLE_HTTP_PROTOCOL,
        http_protocol_used = INTERNET_OPTION_HTTP_PROTOCOL_USED,
        encode_extra = INTERNET_OPTION_ENCODE_EXTRA,
        hsts = INTERNET_OPTION_HSTS,
        enterprise_context = INTERNET_OPTION_ENTERPRISE_CONTEXT,
        connection_filter = INTERNET_OPTION_CONNECTION_FILTER,
        referer_token_binding_hostname = INTERNET_OPTION_REFERER_TOKEN_BINDING_HOSTNAME,
        token_binding_public_key = INTERNET_OPTION_TOKEN_BINDING_PUBLIC_KEY,
        cookies_same_site_level = INTERNET_OPTION_COOKIES_SAME_SITE_LEVEL,
    };

	CXFTP() : hInternet(nullptr), hFtpSession(nullptr), lastError(0) {}

	virtual ~CXFTP()
    {
		close();
	}

	bool connect(const CXText& address, const CXText& username, const CXText& password)
	{
		hInternet = InternetOpen(L"CXFTP", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
		if (!hInternet)
		{
			updateLastError();
			return false;
		}

		hFtpSession = InternetConnect(hInternet, address.get(), INTERNET_DEFAULT_FTP_PORT, username.get(), password.get(), INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
		if (!hFtpSession)
		{
			updateLastError();
			return false;
		}

		return true;
	}

	bool close()
	{
		if (hFtpSession)
		{
			InternetCloseHandle(hFtpSession);
			hFtpSession = nullptr;
		}

		if (hInternet)
		{
			InternetCloseHandle(hInternet);
			hInternet = nullptr;
		}

		return true;
	}

	CXText getLastErrorMessage()
	{
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			lastError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)&lpMsgBuf,
			0, NULL);

		std::wstring message((LPWSTR)lpMsgBuf);
		LocalFree(lpMsgBuf);
		return message.c_str();
	}

	bool put(const CXText& src, const CXText& dst)
	{
		return FtpPutFileW(hFtpSession, src.get(), dst.get(), dwFlags, 0) == TRUE;
	}

	bool get(const CXText& src, const CXText& dst)
	{
		return FtpGetFileW(hFtpSession, src.get(), dst.get(), FALSE, FILE_ATTRIBUTE_NORMAL, dwFlags, 0) == TRUE;
	}

	bool removeFile(const CXText& name)
	{
		return FtpDeleteFile(hFtpSession, name.get()) == TRUE;
	}

	bool removeDir(const CXText& dir)
	{
		return FtpRemoveDirectory(hFtpSession, dir.get()) == TRUE;
	}

	bool rename(const CXText& name, const CXText& newName)
	{
		return FtpRenameFile(hFtpSession, name.get(), newName.get()) == TRUE;
	}

	bool mkdir(const CXText& dir)
	{
		return FtpCreateDirectory(hFtpSession, dir.get()) == TRUE;
	}

	bool enumFiles(const CXText& dir, CXVector<CXText>* results)
	{
		if (!results)
		{
			return false;
		}

		// 枚举目录中的文件和子目录
		WIN32_FIND_DATA findFileData;
		HINTERNET hFind = FtpFindFirstFile(hFtpSession, dir.get(), &findFileData, dwFlags, 0);
		if (hFind == NULL)
		{
			return false;
		}

		do
		{
			if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				// 如果是文件，则添加到结果中
				results->add(findFileData.cFileName);
			}
			else
			{
				// 如果是目录，则递归调用
				if (wcscmp(findFileData.cFileName, L".") != 0 && wcscmp(findFileData.cFileName, L"..") != 0)
				{
					enumFiles(dir + L"/" + findFileData.cFileName, results);
				}
			}
		} while (InternetFindNextFile(hFind, &findFileData));

		InternetCloseHandle(hFind);
		return true;
	}

	bool searchFile(const CXText& name, CXVector<CXText>* results)
	{
		if (!results)
		{
			return false;
		}

		// 枚举目录中的文件和子目录
		WIN32_FIND_DATA findFileData;
		HINTERNET hFind = FtpFindFirstFile(hFtpSession, L"*", &findFileData, dwFlags, 0);
		if (hFind == NULL)
		{
			return false;
		}

		do
		{
			if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				// 如果是文件，则添加到结果中
				if (wcscmp(findFileData.cFileName, name.get()) == 0)
				{
					results->add(findFileData.cFileName);
				}
			}
			else
			{
				// 如果是目录，则递归调用
				if (wcscmp(findFileData.cFileName, L".") != 0 && wcscmp(findFileData.cFileName, L"..") != 0)
				{
					searchFile(name, results);
				}
			}
		} while (InternetFindNextFile(hFind, &findFileData));

		InternetCloseHandle(hFind);
		return true;
	}

	// 读取纯文本文件
	bool read(const CXText& fileName, CXText& content)
	{
		CXTextA binaryContent;
		if (!readBinary(fileName, binaryContent))
		{
			return false;
		}

		// 将二进制内容转换为宽字符串
		std::wstring w = (wchar_t*)(binaryContent.get());
		content = w.c_str();
		return true;
	}

	int getLastError()
	{
		return lastError;
	}

	// 设置 FTP 操作的参数
	bool set(int value)
	{
		dwFlags = static_cast<DWORD>(value);
		return true;
	}

	// 查询文件大小
	int size(const CXText& fileName)
	{
		HINTERNET hFile = FtpOpenFile(hFtpSession, fileName.get(), GENERIC_READ, FTP_TRANSFER_TYPE_BINARY, 0);
		if (!hFile)
		{
			updateLastError();
			return -1;
		}

		DWORD dwFileSize = FtpGetFileSize(hFile, NULL);
		if (dwFileSize == INVALID_FILE_SIZE)
		{
			updateLastError();
			InternetCloseHandle(hFile);
			return -1;
		}

		InternetCloseHandle(hFile);
		return static_cast<long long>(dwFileSize);
	}

	// 读取二进制文件
	bool readBinary(const CXText& fileName, CXTextA& content)
	{
		HINTERNET hFile = FtpOpenFile(hFtpSession, fileName.get(), GENERIC_READ, FTP_TRANSFER_TYPE_BINARY | INTERNET_FLAG_RELOAD, 0);
		if (!hFile)
		{
			updateLastError();
			return false;
		}

		char buffer[1024] = {};
		DWORD bytesRead;
		std::string scontent;
		while (InternetReadFile(hFile, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0)
		{
			scontent.append(buffer, buffer + bytesRead);
		}

		InternetCloseHandle(hFile);

		content = scontent.c_str();
		return true;
	}

	// 写入纯文本文件
	bool write(const CXText& fileName, const CXText& content)
	{
		// 将宽字符串转换为二进制数据
		std::string binaryContent((char*)content.get());
		return writeBinary(fileName, binaryContent);
	}

	// 写入二进制文件
	bool writeBinary(const CXText& fileName, const CXTextA& content)
	{
		HINTERNET hFile = FtpOpenFile(hFtpSession, fileName.get(), GENERIC_WRITE, FTP_TRANSFER_TYPE_BINARY | INTERNET_FLAG_RELOAD, 0);
		if (!hFile)
		{
			updateLastError();
			return false;
		}

		DWORD bytesWritten;
		InternetWriteFile(hFile, content.get(), content.size(), &bytesWritten);

		InternetCloseHandle(hFile);
		return bytesWritten == content.size();
	}

    bool cmd(const CXText& command, CXText& response)
    {
        DWORD bytesRead;
        char buffer[1024] = {};
        HINTERNET hFtpCommand = NULL;

        if (!FtpCommandW(hFtpSession, TRUE, FTP_TRANSFER_TYPE_ASCII, command.get(), 0, &hFtpCommand) || !hFtpCommand) {
            updateLastError();
            return false;
        }

		std::wstring wresponse;
        while (InternetReadFile(hFtpCommand, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead > 0) {
            buffer[bytesRead] = '\0'; // 确保字符串以 null 结尾
            wresponse.append(buffer, buffer + bytesRead);
        }

        InternetCloseHandle(hFtpCommand);

		response = wresponse.c_str();
        return true;
    }

	HINTERNET getHConnect()
	{
		return hFtpSession;
	}

    //其他网路设置
    bool setOption(NetOption dwOption, const CXText& value)
    {
        return InternetSetOption(hFtpSession, dwOption, (LPVOID)value.get(), value.size());
    }
    
    bool setOption(NetOption dwOption, int value)
    {
        return InternetSetOption(hFtpSession, dwOption, &value, sizeof(value));
    }

	bool setCallback(INTERNET_STATUS_CALLBACK callback)
	{
		return InternetSetStatusCallbackW(hFtpSession, callback) == INTERNET_INVALID_STATUS_CALLBACK;
	}
private:
//@隐藏{
	HINTERNET hInternet;
	HINTERNET hFtpSession;
	DWORD lastError;
	DWORD dwFlags = FTP_TRANSFER_TYPE_BINARY; // 默认为二进制传输模式

	void updateLastError()
	{
		lastError = GetLastError();
	}
//@隐藏}
};

//@分组}

