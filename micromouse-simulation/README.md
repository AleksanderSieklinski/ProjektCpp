Wstępna analiza funkcjonalna aplikacji Micromouse

1. Opis działania programu

Program symuluje przejście robota typu Micromouse przez labirynt. Robot posiada czujniki i podejmuje decyzje o ruchu wyłącznie na podstawie lokalnie dostępnych danych. Użytkownik może obserwować wizualizację ruchu robota w czasie rzeczywistym oraz modyfikować parametry symulacji.

Główne funkcjonalności:

Generowanie labiryntu – możliwość tworzenia losowych labiryntów.

Symulacja ruchu robota – robot porusza się zgodnie z algorytmem opartym na lokalnych danych zbieranych przez jego czujniki.

Wizualizacja – podgląd na żywo z możliwością śledzenia decyzji podejmowanych przez robota.

Logowanie danych – zapis i analiza ścieżki przebytej przez robota, liczba odwiedzonych pól, czas rozwiązania labiryntu

2. Szkic interfejsu użytkownika

Główne elementy UI:

Obszar wizualizacji – centralne miejsce, gdzie wyświetlany jest labirynt i pozycja robota.

Panel sterowania – przyciski do uruchamiania, pauzowania i resetowania symulacji, możliwość generowania labiryntów.

Panel informacji – wyświetlanie aktualnych danych, takich jak pozycja robota, liczba odwiedzonych pól, czas symulacji.

Szkic UI:

3. Środowisko programistyczne i technologie

Język programowania: C++

Środowisko: QtCreator (dla GUI) / Visual Studio Code

Biblioteki:

Qt – do implementacji graficznego interfejsu użytkownika

STL – operacje na strukturach danych

random – generowanie losowych labiryntów

fstream – zapisywanie i odczytywanie danych symulacji

Możliwa implementacja logiki ruchu robota obejmuje algorytmy takie jak Algorytm Dijkstry, algorytm A* lub algorytm FloodFill. Końcowa ilość algorytmów będzie zależna od stopnia skomplikowania implementacji.

4. Podsumowanie

Aplikacja umożliwi symulację przejścia robota Micromouse przez labirynt z realistycznym podejmowaniem decyzji na podstawie lokalnych danych. Zastosowanie wizualizacji pozwoli na obserwację i analizę działania różnych algorytmów. Program będzie dostosowywalny poprzez możliwość zmiany parametrów oraz generowania nowych labiryntów.

