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

Video renderer je python progam, který se spouští z root složky pomocí `python renderer.py`. Vstupní data pocházejí z frame generatoru, nebo při testování z fake generátoru.

Fake generátor se spouští pomocí `python fake_frame_generator.py` a vytváří soubory ve složce video_renderer/fake_frames, kterou i vytváří.

## Poznámky
- .gitignore je Chat-GPT generovaný soubor, který má fungovat obstojně pro c++ / pythoon / VSCode projekty. Pomalu se rozrůstá.