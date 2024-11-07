# Semestrální projekt pro PIA1

Michal Tonhajzer

Michal Redhammer

Josef Lát

## Cíle

- c++ program, který simuluje dvě populace pohybujících se organismů, které soupeří o zdroje. Výstupem je poloha a směr všech entit v každém časovém kroku.
- python program, který na základě spočtených dat vygeneruje krátké video, na kterém bude patrný pohyb a vývoj

## Frame generator

(sem patří dokumentace c++ programu)

## Video renderer

Python v tomto projektu využívá některé knihovny, které nejsou součástí standard library:
- matplotlib

Pro čisté použití je nutná příprava prostředí:
1. instalace `pip`
2. instalace pipenv pomocí `pip install pipenv`
3. pomocí `cd` donavigujte do root složky projektu
4. založení nového virtuálního prostředí a instalace potřebných knihoven pomocí `pipenv install` (pipenv nainstaluje knihovny pomocí záznamů v Pipfile a Pipfile.lock)
5. aktivování prostředí pomocí `pipenv shell`
Po ukončení práce je možné prostředí ukončit pomocí `exit`


Video renderer je python progam, který se spouští z root složky pomocí `python renderer.py`. Vstupní data pocházejí z text frame generatoru, nebo při testování z testovacího generátoru.

Testovací text frame generátor se spouští pomocí `python test_text_frame_generator.py` a generuje soubory ve složce video_renderer/test_text_frames, kterou i vytváří.

## Poznámky
- .gitignore je Chat-GPT generovaný soubor, který má fungovat obstojně pro c++ / python / VSCode projekty. Pomalu se rozrůstá.