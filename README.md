# TP Programmation Système ENSEASH

##Objectif
L'objectif de ce TP (2 séances de 4h, sujet en pdf) est de créer un micro shell en C sous Unix.

##Fonctionnalités :
- Commandes simples et avec argument
- Fonction exit ou ctrl D pour sortir du shell
- Affichage du code de retour de la fonction précédente
- Mesure du temps d'exécution du programme précédent
- Gestion des redirections avec possibilitée de les chainer

##Compilation :

Pour lancer le projet, ouvrez un terminal Bash dans le répertoire et réalisez la commande make (ou make -B pour tout recompiler) puis lancez ./TP_main.
La fonction associée à chaque question peut être décommentée dans TP_main pour tester les 1ères questions

Les fichiers test1.txt et test2.txt permettent d'exérimenter avec les redirections en les chaînant par exemple :
echo "message" >  test1.txt >  test2.txt va écrire dans test2.txt

##Commentaires
Seules quelques fonctions basiques sont accessible mais cet exercie a été très utile pour comprendre et appliquer le cours de majeure en programmation système. Nous essayons de poursuivre le projet en travaillant sur la fonction pipe (Q8)

Nous avons décidé de séparer les questions en différents fichiers et de laisser en annotation les versions précédentes car nous avons trouvé cette structure plus simple pour naviguer d'un fichier à un autre que l'utilisation du versioning pour ce TP. En effet ce TP ayant un but pédagogique il nous a semblé important d'avoir un accès facile aux versions précédentes aux notes des erreurs à ne pas refaire.