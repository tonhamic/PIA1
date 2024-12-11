# Semestrální projekt pro PIA1

Michal Tonhajzer

Michal Redhammer

Josef Lát

## Cíle

- ukázkové video jako výsledek práce je ke shlédnutí [zde](https://youtu.be/x6zcPvuZ-Q4).

- c++ program, který simuluje dvě populace pohybujících se organismů, které soupeří o čas a přežití. Výstupem je poloha a směr všech predátorů a kořistí v každém časovém kroku. Pohyb kořisti je inspirovaný pravidly popsanými v [Boids algorithm](https://en.wikipedia.org/wiki/Boids). 
- python program, který na základě spočtených dat vygeneruje krátké video, na kterém bude patrný vývoj populací a pohyb jednotlivých organismů
- parametry simulace:
    - velikost prostoru 1280 × 720 px (HD or 720p)
    - framerate 30 fps
    - počáteční počet predátorů a kořisti
    - rychlost predátorů a kkořisti, udávaná v pixelech/frame (ppf)
    - čas potřebný pro reprodukci kořisti a pro úmrtí predátorů, udaný v počtu snímků
    - poloměr dohledu kořisti
    - intenzita shlukování, alignmentu směru a zdrhání od predátorů
    - poloměr "osobního prostoru" kořisti a intenzita vzájemného odpuzování
    - poloměr dohledu predátorů, intenzita pronásledování kořisti
- parametry vizualizace:
    - velikost a barva zvířat

## Data generator

Frame generator je c++ program, který generuje polohy a směry všech zvířat. Každé zvíře je objekt, který vypadá následovně:

Class Animal:
- x: poloha ve směru x, počátek je v levém spodním rohu obrazovky
- y: poloha ve směru y

Dále existují dvě třídy potomků Animal: Predator a Prey. V nich je implementována veškerá další funkcionalita.

Do výsledných snímků se zapisuje pouze poloha a vektor rychlosti. Predátoři jsou od Kořisti odděleni jedním prázdným řádkem.
Preklada sa zo slozky data generator prikazom make.
Spusta sa pomocou prikazu ./simulation

## Video renderer

Python v tomto projektu využívá některé knihovny, které nejsou součástí standard library:
- Pillow
- opencv-python

Pro čisté použití je nutná příprava prostředí:
1. instalace `pip`
2. instalace pipenv pomocí `pip install pipenv`
3. pomocí `cd` donavigujte do root složky projektu
4. založení nového virtuálního prostředí a instalace potřebných knihoven pomocí `pipenv install` (pipenv nainstaluje knihovny pomocí záznamů v Pipfile a Pipfile.lock)
5. aktivování prostředí pomocí `pipenv shell`.
Po ukončení práce je možné prostředí ukončit pomocí `exit`


Video renderer je python progam, který se spouští z root složky pomocí `python renderer.py`. Vstupní data pocházejí z text frame generatoru, výsledkem je:
- složka jednotlivých snímků
- finální .mp4 video