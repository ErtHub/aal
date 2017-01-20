# aal
----------------------------------------------------------------------------
Hubert Jatkowski 269300
----------------------------------------------------------------------------
Niniejszy program stanowi propozycję rozwiązania problemu "Frog Jump" - patrz dokumentacja końcowa.
----------------------------------------------------------------------------
Uruchamianie: Przez wprowadzenie w linii poleceń nazwy pliku wykonywalnego.
Dane w trybie domyślnym wprowadza się z klawiatury w postaci kolejnych liczb oddzielonych spacjami, np. (0 1 3 5 8 10). Wciśnięcie Enter zatwierdza przypadek testowy i pozwala na wprowadzenie kolejnego. Zatwierdzenie pustej linii zakańcza wprowadzanie.
Przy uruchamianiu można posłużyć się opcjonalnymi parametrami, zmieniającymi domyślne działanie programu:
- -t lub --timer uruchamia pomiar czasu dla rozwiązywania każdej instancji problemu
- -g lub --generate-args wyłącza wprowadzanie przypadków z klawiatury i uruchamia generator instancji problemów. Alternatywnie, -gX lub --generate-extreme powoduje generację przypadków specjalnych do testowania granic złożoności czasowej algorytmu. Opcjonalnie, po tym argumencie, można podać od 1 do 4 dla -g i --generate-args i od 1 do 3 dla -gX i --generate-extreme argumenty liczbowe, które oznaczają kolejno: maksymalną generowaną długość instancji problemu, minimalną długość, gradient, co który jest wybierana kolejna długość instancji problemu oraz ilość generowanych instancji dla każdej długości z osobna. Każdy z tych argumentów musi być niezerową liczbą naturalną.
- -a oznacza wybór algorytmu. Litera wprowadzona po 'a', oznacza wybrany do testowania algorytm, np. -aI oznacza, że będzie testowany algorytm 'I'. Domyślnie wybrany jest algorytm D.
-----------------------------------------------------------------------------
Dane wejściowe programu są przedstawione w postaci wektorów liczb całkowitych. Wyniki wykonania algorytmów dla podanych instancji problemu są przedstawiane na ekranie w postaci listy bloków zawierających: treść instancji problemu i wynik wykonania (0 albo 1). Opcjonalnie podawany jest też wynik oczekiwany i czas wykonania. W trybie uruchomienia z pomiarem czasu i automatyczną generacją instancji, zostanią wyświetlone tabele, obrazujące wyniki średnich i maksymalnych pomiarów czasu dla każdej przyjętej długości instancji problemu na tle szacowanych złożoności algorytmów.
-----------------------------------------------------------------------------
Rozwiązanie zadanego problemu stanowi zestawienie algorytmów: przeszukiwania wstecz z przycinaniem, iteracyjnego przeszukiwania z zapamiętywaniem oraz rekurencyjnego przeszukiwania z zapamiętywaniem. Ostatni z wymienionych algorytmów korzysta w rozwiązywaniu problemu z kontenera biblioteki standardowej typu unordered_map. Więcej informacji o algorytmach w dokumentacji końcowej.
-----------------------------------------------------------------------------
Implementacja programu, oprócz pliku main.cpp, została podzielona na następujące moduły:
- algorithms.hpp - zawiera implementacje badanych algorytmów oraz struktury danych nimi zarządzające
- ArgGetter.h i ArgGetter.cpp - implementacja procedury sczytującej argumenty  wywołania algorytmów z wybranych wejść.
- Solver.h i Solver.cpp - klasa podstawowego egzekutora algorytmów - w konstruktorze przyjmuje wskaźnik na funkcję wykonującą wybrany algorytm. Użycie konstruktora podstawowego jest zabronione.
- TimerSolver.h i TimerSolver.cpp - rozszerzenie podstawowej klasy Solver o możliwość rejestrowania w osobnej strukturze danych czasów wykonania algorytmów.
- PIGenerator.h i PIGenerator.cpp - pomocnicza klasa tworząca losowe instancje zadanego problemu - włączana przez algorithms.hpp.
-----------------------------------------------------------------------------
- Poprawne rozwiązanie problemu jest gwarantowane dla długości wejściowego wektora nie większej niż 1100 liczb i dla liczb nie większych niż 2^31-1.
- Generator instancji problemu może działać na dwa sposoby: tworzyć specjalne do celów testów wytrzymałościowych dla algorytmów przypadki testowe dla zadanej długości o z góry narzuconej i znanej postaci lub generować przypadek losowy dla zadanej długości i oczekiwanej wartości zwracanej przez algorytm poprzez losowania kolejnych liczb do ciągu z przedziału <poprzednia liczba + 1; poprzednia liczba + poprzednia długość skoku +1> w ten sposób, że każda kolejna liczba w tym przedziale ma o pewną stałą wartość skokową większe prawdopodobieństwo wylosowania, niż poprzednia. Losowanie jest powtarzane, dopóki nie osiągniemy zadanej długości problemu.
