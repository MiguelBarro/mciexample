#include <chrono>
#include <thread>

#define WIN32_LEAN_AND_MEAN

#include "mciAssert.hpp"

#include <fcntl.h>
#include <io.h>
#include <ConsoleApi2.h>

using namespace std::chrono_literals;

// https://learn.microsoft.com/en-us/windows/win32/multimedia/device-types
void playing_mp3();
void playing_wav();
void playing_vim_wav();
void playing_vim_wav_unicode();

int main()
{
    try
    {
//      playing_mp3();
//      playing_wav();
//      playing_vim_wav();
        playing_vim_wav_unicode();
    }
    catch (std::basic_string<TCHAR> e)
    {
        terr << TEXT("Error: ") << e << std::endl;
        return -1;
    }

    return 0;
}

void playing_mp3()
{
    // open a media file
    LPTSTR open_command = TEXT(
            R"(open C:\Users\migue\Music\turbolaser.mp3 type mpegvideo alias laser)"
            );
    tout << open_command << std::endl;
    mciAssert(mciSendString(open_command, nullptr, 0, nullptr));

    // play media file
    // LPTSTR play_command = TEXT("play laser wait"); // wait till end
    LPTSTR play_command = TEXT("play laser");
    tout << play_command << std::endl;
    mciAssert(mciSendString(play_command, nullptr, 0, nullptr));

    // query status
    bool end = false;
    LPTSTR status_commands[] = {
        TEXT("status laser ready"),
        TEXT("status laser mode")
    };

    // This loop is just to show how status change. Can be avoided using the
    // 'play' command with the flag 'wait'
    while (!end)
    {
        for ( LPTSTR status_command : status_commands )
        {
            std::basic_string<TCHAR> buffer(256, TEXT('\0'));

            tout << status_command << std::endl;
            mciAssert(mciSendString(status_command, buffer.data(), buffer.size(), nullptr));
            tout << TEXT("Status: ") << buffer << std::endl;

            end = std::basic_string<TCHAR>::npos != buffer.find(TEXT("stopped"));
        }

        std::this_thread::sleep_for(1s);
    }

    // close media file
    LPTSTR close_command = TEXT("close laser");
    tout << close_command << std::endl;
    mciAssert(mciSendString(close_command, nullptr, 0, nullptr));
}

void playing_vim_wav_unicode()
{
    _setmode(_fileno(stdout), _O_WTEXT);
    SetConsoleOutputCP(65001);

    // open a media file
    LPWSTR open_command = LR"(open "C:\Users\migue\AppData\Local\Temp\мир.wav" alias sound1)";
//  LPWSTR open_command = L"open \"C:\\Users\\migue\\AppData\\Local\\Temp\\мир.wav\" alias sound1";
//  LPWSTR open_command = L"open \"C:\\Users\\migue\\AppData\\Local\\Temp\\\u043c\u0438\u0440.wav\" alias sound1";
    std::wcout << open_command << std::endl;
    mciAssert(mciSendStringW(open_command, nullptr, 0, nullptr));

    // play media file
    LPWSTR play_command = L"play sound1 wait"; // wait till end
    std::wcout << play_command << std::endl;
    mciAssert(mciSendStringW(play_command, nullptr, 0, nullptr));

    // close media file
    LPWSTR close_command = L"close sound1";
    std::wcout << close_command << std::endl;
    mciAssert(mciSendStringW(close_command, nullptr, 0, nullptr));

}

void playing_vim_wav()
{
    // open a media file
    LPTSTR open_command = TEXT(
//      R"(open 'C:\Users\migue\vimfiles\plugin\typewriter.vim\autoload/../sounds/carriage1.wav' alias sound1)"
//works R"(open C:\Users\migue\vimfiles\plugin\typewriter.vim\sounds\carriage1.wav alias sound1)"
//works R"(open C:\Users\migue\vimfiles\plugin\typewriter.vim\autoload/../sounds/carriage1.wav alias sound1)"
        R"(open "C:\Users\migue\vimfiles\plugin\typewriter.vim\autoload/../sounds/carriage1.wav" alias sound1)"
            );
    tout << open_command << std::endl;
    mciAssert(mciSendString(open_command, nullptr, 0, nullptr));

    // play media file
    LPTSTR play_command = TEXT("play sound1 wait"); // wait till end
    tout << play_command << std::endl;
    mciAssert(mciSendString(play_command, nullptr, 0, nullptr));

    // close media file
    LPTSTR close_command = TEXT("close sound1");
    tout << close_command << std::endl;
    mciAssert(mciSendString(close_command, nullptr, 0, nullptr));

}

void playing_wav()
{
    // open a media file
    LPTSTR open_command = TEXT(
            R"(open C:\Users\migue\Music\ding1.wav alias ding)"
            );
    tout << open_command << std::endl;
    mciAssert(mciSendString(open_command, nullptr, 0, nullptr));

    // play media file
    LPTSTR play_command = TEXT("play ding wait"); // wait till end
    tout << play_command << std::endl;
    mciAssert(mciSendString(play_command, nullptr, 0, nullptr));

    // close media file
    LPTSTR close_command = TEXT("close ding");
    tout << close_command << std::endl;
    mciAssert(mciSendString(close_command, nullptr, 0, nullptr));
}
