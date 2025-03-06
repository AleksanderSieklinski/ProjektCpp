Projekt zaliczeniowy z przedmiotu Zaawansowane C++<br>
Aleksander Siekliński, 2025

Wstępna analiza funkcjonalna aplikacji Micromouse

1. **Opis działania programu**

Program symuluje przejście robota typu Micromouse przez labirynt. Robot posiada czujniki i podejmuje decyzje o ruchu wyłącznie na podstawie lokalnie dostępnych danych. Użytkownik może obserwować wizualizację ruchu robota w czasie rzeczywistym.

2. **Główne funkcjonalności:**

Generowanie labiryntu – możliwość tworzenia losowych labiryntów.

Symulacja ruchu robota – robot porusza się zgodnie z algorytmem opartym na lokalnych danych zbieranych przez jego czujniki.

Wizualizacja – podgląd na żywo z możliwością śledzenia decyzji podejmowanych przez robota.

Logowanie danych – zapis i analiza ścieżki przebytej przez robota, liczba odwiedzonych pól, czas rozwiązania labiryntu

3. **Szkic interfejsu użytkownika**

Główne elementy UI:

Obszar wizualizacji – centralne miejsce, gdzie wyświetlany jest labirynt i pozycja robota.

Panel sterowania – przyciski do uruchamiania i resetowania symulacji oraz możliwość generowania labiryntów.

Panel informacji – wyświetlanie aktualnych danych, takich jak pozycja robota, liczba odwiedzonych pól oraz czas symulacji.

Szkic UI znajduje się w pliku `micromouse_ui.png`.

4. **Środowisko programistyczne i technologie**

Język programowania: C++

Środowisko: QtCreator (dla GUI) / Clion

Biblioteki:

Qt – do implementacji graficznego interfejsu użytkownika

STL – operacje na strukturach danych

Implementacja ruchu robota odbędzie się przy pomocy algorytmu Flood Fill, wizualizacja będzie oparta na bibliotece Qt, a generowanie labiryntów będzie realizowane przy pomocy algorytmu Randomized Depth-First Search.

5. **Podsumowanie**

Aplikacja umożliwi symulację przejścia robota Micromouse przez labirynt wstępnie w celu poszukiwania optymalnej ścieżki a następnie ponownie w oparciu o wcześniej pozyskane informacje w jak najkrótszym czasie. Użytkownik będzie mógł obserwować przebieg symulacji w czasie rzeczywistym oraz analizować zebrane dane. Program będzie również umożliwiał generowanie losowych labiryntów, co pozwoli na testowanie algorytmów na różnych konfiguracjach labiryntu.

