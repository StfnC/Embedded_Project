# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Machines à états finis logicielles
+ Section #  : 3
+ Équipe #   : 54
+ Correcteur : Charles Jiang

# LISIBILITÉ
## En-têtes en début de programme   

| Pénalité par erreur                          | -1.5       |
| -------------------------------------------- | ---------- |
| Noms des auteurs                             |            |
| Description du programme                     |            |
| Identifications matérielles (Broches I/O)    |            |
| Table des états ou autres s'il y a lieu      |            |
| __Résultat partiel__                         | __(1.5/1.5)__ |

## Identificateurs significatifs (Autodocumentation)

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de *chiffres magiques*               | (/0.5)     |
| Noms de variables décrivent l'intention      | (0/0.5)     |
| Noms de fonctions décrivent l'intention      | (/0.5)     |
| __Résultat partiel__                         | __(1/1.5)__ |

variable machine -> represente l'etat de la machine et non juste machine


## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme 
 + Procédure peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'Internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| __Résultat partiel__                         | __(1/1.0)__ |


## Indentation   

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Indentation structurée                       | (0/0.5)     |
| Indentation uniforme dans le programme       | (/0.5)     |
| __Résultat partiel__                         | __(0.5/1.0)__ |

indentation pb2 ligne 41 de enum class


# MODULARITÉ ET COMPRÉHENSION
## Fonctions bien définies

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Responsabilité unique d'une fonction         |            |
| Maximum de 4 paramètres                      |            |
| Absence de code dupliqué                     |            |
| etc                                          |            |
| __Résultat partiel__                         | __(1/1.0)__ |

fonction tres bien faites bravo!


## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0       |
| -------------------------------------------- | ---------- |
| Utilisation appropriée des registres         |            |
| Machine à états codée clairement             |            |
| Délais et minuteries utilisés judicieusement |            |
| PWM bien établi                              |            |
| Scrutation et interruptions bien utilisées   |            |
| etc                                          |            |
| __Résultat partiel__                         | __(4/4.0)__ |

# FONCTIONNALITÉS
## Git

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Fichiers aux bons endroits                   | (/1.5)     |
| Absence de fichiers inutiles                 | (/1.5)     |
| __Résultat partiel__                         | __(3/3.0)__ |


## Compilation    

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de messages d'erreurs de compilation | (/1.5)     |
| Absence de messages d'attention (*warning*)  | (/0.5)     |
| __Résultat partiel__                         | __(2/2.0)__ |
   

## Évaluation boîte noire  

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Cas normal de fonctionnement                 | (1.5/2.5)     |
| Cas limites observables                      | (1.5/2.5)     |
| __Résultat partiel__                         | __(3/5.0)__ |

pb1 ne s'allume pas, surement a cause des setColor(OFF) dans le dernier state au lieu de setColor(RED)

# Résultat

__Total des points: 17.0/20__

# Commentaires du correcteur:


# Basé sur le commit suivant
```
commit 2e7d706e644263aa756772ee7f1e9eccea41260d
Author: Faneva Rakotoarivony <faneva.rakotoarivony@polymtl.ca>
Date:   Fri Jan 28 14:12:25 2022 -0500

    Supprimer LISEZ-MOI.txt
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp2/pb1`
```
make : on entre dans le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/54/tp/tp2/pb1 »
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c main.cpp
avr-gcc -Wl,-Map,pb1.elf.map -mmcu=atmega324pa -o pb1.elf  main.o \
-lm 
avr-objcopy -j .text -j .data \
	-O ihex pb1.elf pb1.hex
make : on quitte le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/54/tp/tp2/pb1 »

```

## Sortie de `make` dans `tp/tp2/pb2`
```
make : on entre dans le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/54/tp/tp2/pb2 »
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c main.cpp
avr-gcc -Wl,-Map,pb1.elf.map -mmcu=atmega324pa -o pb1.elf  main.o \
-lm 
avr-objcopy -j .text -j .data \
	-O ihex pb1.elf pb1.hex
make : on quitte le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/54/tp/tp2/pb2 »

```
