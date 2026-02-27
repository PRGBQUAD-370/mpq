#include <Windows.h>
#include <thread>
#include <cstdlib>
#include <cmath>
#pragma comment(lib, "winmm.lib")

// ===================== MUSIC CODE =====================

VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t ^ t * (t >> (t >> 8 & 9) & 50) | t * 4));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t ^ t * (t >> (t >> 8 & 10) & 40) | t * 4));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * ((t >> 12 | t >> 6) & 69 & t >> 3) | t * 4 | t * (t >> 9));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[11025 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t >> 6 & t >> 2));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI playWav(const char* filename) {
    PlaySoundA(filename, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}

VOID WINAPI sound5() {
    playWav("sound5.wav");
}

VOID WINAPI sound8() {
    playWav("sound8.wav");
}

DWORD WINAPI MusicThread(LPVOID) {
    while (true) {
        sound1();   Sleep(30000);
        sound2();   Sleep(30000);
        sound5();   Sleep(30000);
        sound3();   Sleep(30000);
        sound4();   Sleep(30000);
        sound8();   Sleep(30000);
    }
    return 0;
}

// ===================== GDI EFFECTS =====================
void EffectInvert(HDC hdc, int w, int h) { PatBlt(hdc, 0, 0, w, h, DSTINVERT); }
void EffectWave(HDC hdc, int w, int h) { 
    static int t = 0; 
    for (int y = 0; y < h; y++) { 
        int x = (int)(10 * sin((y + t) * 0.05)); 
        BitBlt(hdc, x, y, w, 1, hdc, 0, y, SRCCOPY); 
    } 
    t += 4; 
}
void EffectStretch(HDC hdc, int w, int h) { 
    StretchBlt(hdc, rand() % 50, rand() % 50, w - 100, h - 100, hdc, 0, 0, w, h, SRCCOPY); 
}
void EffectMelt(HDC hdc, int w, int h) { 
    for (int x = 0; x < w; x += 5) 
        BitBlt(hdc, x, rand() % 10, 5, h, hdc, x, 0, SRCCOPY); 
}
void EffectRGBShift(HDC hdc, int w, int h) { 
    BitBlt(hdc, 5, 0, w, h, hdc, 0, 0, SRCCOPY); 
    BitBlt(hdc, -5, 5, w, h, hdc, 0, 0, SRCAND); 
}
void EffectScanlines(HDC hdc, int w, int h) { 
    for (int y = 0; y < h; y += 3) 
        BitBlt(hdc, rand() % 5, y, w, 1, hdc, 0, y, SRCCOPY); 
}

// ======================== MAIN ========================
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // First message box
    int result1 = MessageBoxA(
        NULL,
        "This is a mpq.exe, Malware",
        "mpq.exe",
        MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2
    );
    if (result1 != IDYES) return 0;

    // Second message box – now only ONE LINE
    int result2 = MessageBoxA(
        NULL,
        "Are you sure, it will distroy your bootable device",
        "mpq.exe-Final warning",
        MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2
    );
    if (result2 != IDYES) return 0;

    srand(GetTickCount());
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    CreateThread(NULL, 0, MusicThread, NULL, 0, NULL);

    DWORD startTime = GetTickCount();
    DWORD lastSwitch = startTime;
    int effect = 0;

    while (GetTickCount() - startTime < 300000) { // 5 minutes
        HDC hdc = GetDC(NULL);

        if (GetTickCount() - lastSwitch > 10000) {
            effect = (effect + 1) % 6;
            lastSwitch = GetTickCount();
        }

        switch (effect) {
        case 0: EffectInvert(hdc, w, h); break;
        case 1: EffectWave(hdc, w, h); break;
        case 2: EffectStretch(hdc, w, h); break;
        case 3: EffectMelt(hdc, w, h); break;
        case 4: EffectRGBShift(hdc, w, h); break;
        case 5: EffectScanlines(hdc, w, h); break;
        }

        ReleaseDC(NULL, hdc);
        Sleep(30);
    }

    PlaySound(NULL, NULL, 0);
    ExitProcess(0);
}