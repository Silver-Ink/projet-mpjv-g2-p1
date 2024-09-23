## 09/09/2024
- Création du dépôt GitHub
- Mise en commmun du travail effectué aux séances précédentes

## 12/09/2024
- Classe et macro de tests unitaires
- Quelques tests pour la classe Vec3
- Finitions de la classe Vec3

## 16/09/2024
- Synchronisation et répartition des tâches restantes (le groupe est au complet)
- Intégration d'Euler
- Réflexion sur l'architecture du code en groupe

## 17/09/2024
- Singleton GameContext afin de gérer l'interaction avec le joueur qui ne fait pas directement partie du moteur physique.

## 21/09/2024
- Création des classes des différents tirs de projectiles

## 22/09/2024
- Mise en place des collisions contre les bordures de la fenêtre
- Changement du comportement du laser, passant de flux continu de cercles à une véritable ligne

## Résumé
Nous avons tenté de produire un code propre pour s'assurer une bonne base pour ce moteur physique. 
Il n'y a pas de difficulté en particulier à reporter.
Nous avons profité de cette première phase plus simple pour nous mettre à niveau sur quelques notions de C++, ainsi que pour nous organiser le travail et établir quelques conventions de code et de nommage.

Afin d'éviter de coupler le moteur physique avec tout rendu visuel, nous avons décidé de ranger tout le code du mini-jeu dans un singleton 'GameContext', afin de garder un code propre pour la suite où le projet va se complexifier. Le singleton a pour avantage d'être public, ce qui n'est pas recommandé en soit, mais comme le projet s'articule plus sur le développement du moteur physique que le mini-jeu, cela permet de gagner du temps sur ce deuxième point. 

La classe de test permet de faire des tests simples et rapides, n'impactant pas l'exécution du jeu. Elle pourra facilement être étendue à d'autres classes par la suite.

Enfin, nous avons choisi de rendre la classe *Particle* abstraite, dont tous les types de projectiles héritent, afin de forcer l'implémentation de la fonction draw selon le cas d'usage de la particule. Cela pourra être amené à changer, selon l'utilisation.
