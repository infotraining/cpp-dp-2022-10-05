# Szkolenie - Wzorce projektowe w C++ #

## Dokumentacja + slajdy

* https://infotraining.bitbucket.io/cpp-dp

## Środowisko (2 opcje do wyboru)

  1. Konfiguracja lokalna

     Jeśli uczestnik chce skonfigurować lokalnie swoje środowisko, to należy zainstalować:
     
     * Dowolny kompilator C++ (gcc, clang, Visual C++) wspierający C++17        
     * [CMake > 3.15](https://cmake.org/)
       * proszę sprawdzić wersję w lini poleceń

         ```
         cmake --version
         ```

  2. Zdalna maszyna wirtualna (SSH)
     
     * link do rejestracji: https://labs.azure.com/register/rrteny9y
       - uczestnik powinien mieć konto Github lub Microsoft
       - ustawić swoje hasło przy rejestracji

## IDE - Visual Studio Code

* [Visual Studio Code](https://code.visualstudio.com/)

### Zainstalować wtyczki C++

* C/C++
* CMakeTools
* Live Share
* W przypadku pracy ze zdalną maszyna przez SSH należy za(re)instalować wtyczki C++ po połączeniu z maszyną.

### Zainstalować wtyczkę do pracy zdalnej (jeśli wybrano korzystanie z maszyny wirtualnej)

* Remote - SSH
  - opis pracy z wtyczką: https://code.visualstudio.com/docs/remote/ssh
  - UWAGA! Windows 10 - [wymagana jest instalacja klienta OpenSSH lub Git for Windows (wcześniejsze wersje Windows)](https://code.visualstudio.com/docs/remote/troubleshooting#_installing-a-supported-ssh-client)
  - sprawdzić, czy klient SSH jest dostępny w terminalu (dodany do zmiennej PATH)
  - przy połączeniu z maszyną zdalną należy kliknąć na link **details** w pop-upie w prawym dolnym rogu. Umożliwi to wprowadzenie ustawionego wcześniej hasła.