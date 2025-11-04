## Autor: Jakub Kurek

### Data: 04-11-2025

# Co zawiera

Folder zawiera pliki:

- README - informacje o programie i użyciu
- Makefile - kompilacja, uruchamianie, archiwizacja programów
- src/ - katalog zawierający pliki źródłowe poszczególnych programów oraz biblioteki współdzielonej funkcji:

Katalog src:

- main.cpp
- singlelist.hpp

# Do czego służy

- main.x - Testuje wskaźnikowa implementacjie listy powiązanej

# Jak uruchomić program

```bash
make run # uruchomienie programu z testami
```

# Jak zkompilować

```bash
make
```

Pliki wygonywalne znajdują się w `./target/exe/` a pliki obj w `./target/obj/`

# Po zakończeniu

Wszystkie skompilowane pliki można usunąć przy uzyciu polecenia:

```bash
make clean
```
