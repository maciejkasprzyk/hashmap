## Projekt na przedmiot AAL
Treść zadania w pliku pdf: TIN dokumentacja koncowa

## Hashmapa - W12W2131
Maciej Kasprzyk

## Opis funkcjonalny

Skrypt do pobierania tekstów z API wolnych lektur.
    python data_download.py -> menu tekstowe

Skrypt do generacji słów języka polskiego na podstawie pobranych tekstów.
    generator.py [-n ilość] plik
    ilość - liczba słów do wygenerowania, jeżeli nie podany wygenerowane zostanie maksimum
    plik - plik zawierający teksty książek w formacie JSON

Skrypt do analizowania złożoności czasowej.
    analizator.py words folder n k
    words - ścieżka do pliku txt zawierającego słowa, które mają być użyte do testowania
    folder - folder, w którym zostaną zapisane wykresy i tabela
    n - wielkość tablicy używana strukturze
    k - maksymalna ilość wstawionych elementów, dla których zostanie wykonany pomiar

Jako wynik działania programu zapisane są:
- wykresy czasu działania operacji dodawania, usuwania i enumeracji od wielkości N/100 do N.
- tabele powyższych czasów działania z wyliczonymi q(n) (zgodność teoretycznego czasu działania z otrzymanym)

## Krótki opis rozwiązania
Implememtacja hasmapy znajduje się w pliku hashmap.h.
Oprócz wyżej wymienionych skryptów rozwiązanie składa się z programu main.cpp. Program ten jako argument wywołania przyjmuje parametr K i N. Tworzona jest hashmapa (na tablicy rozmiaru K), do której wstawiane jest N elementów. Program mierzy czas dla wykonania operacji dodania i usunięcia pojedynczego elementu oraz enumeracji wszystkich elementów. Czasy są zwracane na standardowe wyjście. Skrypt analizator.py wielokrotnie wywołuje program main i prezentuje dane uzyskane z programu. 
