## Autor: Jakub Kurek

### Data: 21-10-2025

# Co zawiera

Folder zawiera pliki:

- README - informacje o programie i użyciu
- Makefile - kompilacja, uruchamianie, archiwizacja programów
- src/ - katalog zawierający pliki źródłowe poszczególnych programów oraz biblioteki współdzielonej funkcji:

Katalog src:

- main.cpp
- quicksort.hpp
- mergesort.hpp

# Do czego służy

- main.x - Testuje iteratorową implementacje quicksort oraz mergesort z odpowiednich plików nagłówkowych

# Jak uruchomić program

```bash
make run # uruchomienie programu z testami
```

# Jak zkompilowąć

```bash
make compile
```

Pliki wygonywalne znajdują się w `./target/exe/` a pliki obj w `./target/obj/`

# Po zakończeniu

Wszystkie skompilowane pliki można usunąć przy uzyciu polecenia:

```bash
make clean
```
