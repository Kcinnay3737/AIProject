# Introduction
Pour le cadre de projet pratique 2 dans le cour de AI jai choisis de faire un AI utilisant du reinforcement learning
pour un jeu imitant The Binding of Isaac dans un engin maison en c++. 

# Probleme
1. Le premier problem que j'ai rencontrer c'est fais avec l'importation des libraries, AI-Toolbox contenais des
dependances externe et j'avais du mal a comprendre comment les linker. Pour regler ce probleme jai tanter de faire des recherches
sur comment importer les libraries en question mais sans succes, jai donc demander de l'aide au professeur qui ma bien guider donc
j'ai par la suite fini l'importation des libraries au projet et fais le menage des fichier de celle-ci.

2. Je croyais avoir bien importer mes libraries mais jai rencontrer d'autre probleme car je n'avais pas tout bien regler mes dependance
et je n'avais pas bien inclus tout les fichier cpp necessaire je me suis donc acharner a chercher tout les folder donc j'avais besoin ce 
qui au final jai reussi a trouver.

3. J'ai voulus incorporer la libraries AI toolbox dans la game et non dans l'engine mais cela me causai quelque probleme et je n'arrivais pas
a incorporer les library sans mettre le projet en static lib ce qui ne fonctionne pas donc jai pris la decision de les mettre dans l'engine
et de faire un provider pour permettre a la game d'y acceder.

# Outils choisis et justifications
Comme outils pour m'aider a accomplir la tache jai choisis AI-Toolbox qui est une library contenant plusieur algorithme 
pour faire du reinforcement learning ecrite en c++ ce qui correspond bien a l'objectif que je tentes d'accomplir.

# Processus d'apprentissage

# Entrainement

# Conclusion et retour d'experience (ce qui a fonctionne ou non, les lecons pour l'avenir)