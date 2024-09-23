## 09/09/2024
- Creation du dépot github
- Mise en commmun du travail effectué aux scéances précedentes

## 12/09/2024
- Classe et macro de tests unitaires 
- Quelques tests pour la classe Vec3
- Finitions de la classe Vec3

## 16/09/2024
- Synchronisation et répartition de taches restantes (le groupe est au complet)
- Intégration d'Euler
- Reflection sur l'architecture du code en groupe

## 17/09/2024
- Singleton GameContext pour gérer l'interraction avec le joueur qui ne fait pas directement parti du moteur physique.

## 21/09/2024
- Créations des classes des différents tirs de projectiles

## Résumé
Nous avons tentés de produire un code propre pour s'assurer une bonne base pour ce moteur physique. 
Il n'y a pas de difficulté en particulier a reporter.
Nous avons profités de cette première phase plus simple pour nous mettre à niveau sur quelques notions de C++, ainsi que pour nous organiser le travail et établir quelques conventions de code et de nommage.

Afin d'éviter de coupler le moteur physique avec tout rendu visuel, nous avons décider de ranger tout le code du mini jeu dans un singleton 'GameInstance', afin de garder un code propre pour la suite où le projet va se complexifier. Le singleton a pour avatage d'etre public, ce qui n'est pas recommandé en soit, mais comme le projet s'articule plus sur le développement du moteur physique que le mini jeu, cela permet de gagner du temps sur ce deuxième point. 

La classe de test permet de faire des tests simple et rapides, n'impactant pas l'exécution du jeu. Elle pourra facilement être étendue à d'autres classes par la suite.

Enfin, nous avons choisi de rendre la classe *Particle* abstaite, dont tous types de projectiles héritent, afin de forcer l'implémentation de la fonction draw selon le cas d'usage de la particule. Cela pourra etre amené à changement selon l'utilisation.
