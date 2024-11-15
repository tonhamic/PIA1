# Semestrální projekt pro PIA1

Michal Tonhajzer


Michal Redhammer

Josef Lát

## Cíle

- c++ program, který simuluje dvě populace pohybujících se organismů, které soupeří čas přežití. Výstupem je poloha a směr všech entit v každém časovém kroku.
- python program, který na základě spočtených dat vygeneruje krátké video, na kterém bude patrný vývoj populací a pohyb jednotlivých entit
- parametry simulace:
    - velikost prostoru 1280 × 720 px (HD or 720p)
    - framerate 30 fps
    - počáteční počet ryb a žraloků 
    - rychlost ryb a žraloků, udávaná v pixelech/frame (ppf)
    - čas potřebný pro reprodukci ryb a pro úmrtí žraloků, udaný v počtu snímků
    - velikost zóny podél okrajů, která entity odpuzuje a udržuje je na obrazovce a její intenzita
    - poloměr dohledu ryb
    - intenzita shlukování, alignmentu směru a zdrhání od žraloků
    - poloměr "osobního prostoru" ryb a intenzita vzájemného odpuzování
    - poloměr dohledu žraloků, intenzita pronásledování ryb

## Frame generator

Frame generator je c++ program, který generuje polohy a směry všech entit. Každá entita je objekt, který vypadá následovně:

Class Entity:
- typ: string, rozlišuje mezi rybami a žraloky a tím určuje jejich chování
- x: poloha ve směru x, počátek je v levém spodním rohu obrazovky
- y: poloha ve směru y
- phi: směr pohybu <0, 2pi>. Nulový úhel odpovídá směru osy x.
- t: údaj o čase, udávaný v počtu snímků. Ryby se po chvíli rozmnožují, žraloci po chvíli bez jídla zemřou.

Do výsledných snímků se ale zapisuje pouze typ, poloha a směr. Údaj o čase není pro animaci důležizý.

## Video renderer

Python v tomto projektu využívá některé knihovny, které nejsou součástí standard library:
- matplotlib
- opencv-python

Pro čisté použití je nutná příprava prostředí:
1. instalace `pip`
2. instalace pipenv pomocí `pip install pipenv`
3. pomocí `cd` donavigujte do root složky projektu
4. založení nového virtuálního prostředí a instalace potřebných knihoven pomocí `pipenv install` (pipenv nainstaluje knihovny pomocí záznamů v Pipfile a Pipfile.lock)
5. aktivování prostředí pomocí `pipenv shell`.
Po ukončení práce je možné prostředí ukončit pomocí `exit`


Video renderer je python progam, který se spouští z root složky pomocí `python renderer.py`. Vstupní data pocházejí z text frame generatoru, nebo při testování z testovacího generátoru. Výsledkem je:
- složka jednotlivých snímků
- finální .mp4 video

Testovací text frame generátor se spouští pomocí `python test_text_frame_generator.py` a generuje soubory ve složce video_renderer/test_text_frames, kterou i vytváří.

## Poznámky
- .gitignore je Chat-GPT generovaný soubor, který má fungovat obstojně pro c++ / python / VSCode projekty. Pomalu se rozrůstá.