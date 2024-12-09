Pour compiler le projet :

- [ ] Générer un nouveau projet avec le générateur OpenFrameworks
- [ ] Remplacer le dossier 'src' par celui fourni dans le rendu de la phase I.
- [ ] Ouvrir le .sln
- [ ] Dans l'arborescence, cliquer droit sur le dossier 'src' et faire "inclure au projet"
- [ ] Compiler

# Contrôles

* Création de RigidBody:  **F1-F4** permet de faire apparaitre des RigidBodies avec une densité de plus en plus élevée.

    * **F5** permet également d'activer ou désactiver la gravité pour la création des prochains RigidBodies.

* Impacts: Le **CLIC DROIT** permet de donner un coup de puissance normale, et le **CLIC MOLETTE** un coup plus léger.
Le RigidBody peut recevoir un impact lorsqu'un point blanc est présent, indiquant le lieu exact de l'impact.

* Déplacement: **Z-Q-S-D** permet de se déplacer latéralement.
**SHIFT** et **ESPACE** permettent quant à eux un déplacement sur l'axe vertical.

* Orientation de la caméra: Il est possible de maintenir **CLIC GAUCHE** pour changer la vue de la caméra autour de l'origine.
La **MOLETTE** sert à avancer ou reculer selon la direction de la caméra.

    * Appuyer sur **R** va réinitialiser la caméra à son emplacement d'origine.
    Un **DOUBLE CLIC GAUCHE** permettra au contraire de placer la caméra à un lieu éloigné de l'origine.

* **B** bascule l'affichage des volumes englobants
Les volumes englobants sont en rouge quand ils détectent une collision

* **N** bascule l'affichage de l'historique des normal d'impact entre les RigidBodies

* **O** bascule l'affichage de l'octree
L'octree ne stocke que 2 RigidBodies par niveau, pour réduire le nombre de rigidBody a faire apparaitre pour tester.