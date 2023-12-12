Faire ctrl+shift+f et chercher AI, jai mis ce mot cle en commentaire partout ou je fais du AI

# Introduction
Dans le cadre du projet pratique 2 pour le cours d'AI, j'ai choisi de développer une AI utilisant le reinforcement learning pour
un jeu inspiré de The Binding of Isaac, réalisé avec un moteur fais maison en C++. L'algorithme utilisé est le QLearning.

# Probleme
1. Importation des librairies : J'ai eu des difficultés avec l'importation des librairies, notamment AI-Toolbox, qui nécessitait 
des dépendances externes. Après des recherches sans succes, j'ai demandé de l'aide à mon professeur qui m'a guidé efficacement, 
me permettant ainsi de finaliser l'importation et d'organiser les fichiers les plus pertinents.

2. Gestion des dépendances : Malgré une première importation réussie, des problèmes subsistaient car toutes les dépendances et fichiers 
nécessaires n'étaient pas correctement configurés. Après une recherche approfondie et méticuleuse, j'ai réussi à identifier et à intégrer 
tous les éléments requis.

3. Intégration de la librairie AI-Toolbox : Initialement, j'ai tenté d'intégrer AI-Toolbox dans le jeu et non dans le moteur, ce qui a 
posé des problèmes. Ne pouvant pas intégrer les librairies sans passer le projet en librairie statique, j'ai décidé de les ajouter au 
moteur et de créer un fournisseur pour faciliter l'accès depuis le jeu.

4. Implémentation du QLearning : Lors de ma première intégration de QLearning, j'ai remarqué que la gestion de l'epsilon greedy n'était 
pas incluse par défaut. J'ai donc dû explorer la librairie pour trouver les fonctionnalites en question utiliser une politique d'exploration 
et d'exploitation adéquate.

# Outils choisis et justifications
J'ai choisi AI-Toolbox, une librairie en C++ proposant divers algorithmes pour le reinforcement learning. Ce choix se justifie principalement par 
deux raisons. Premièrement, le fait que la librairie soit écrite en C++ représente un avantage majeur, car cela correspond à mes besoins et compétences 
en programmation. Deuxièmement, AI-Toolbox intègre des fonctions de QLearning, un domaine avec lequel je suis déjà familier. Ainsi, cette librairie me 
permettait de ne pas partir de zéro et d'exploiter mes connaissances préexistantes pour avancer efficacement dans mon projet.

# Processus d'apprentissage
1. Recherche de librairies : J'ai cherché des librairies de reinforcement learning en C++ et ai découvert AI-Toolbox, qui semblait répondre à mes besoins.

2. Documentation et modèles MDP : Par la suite je me suis documenter sur la page git ainsi que sur la documentation et jai vue que la library contenais plusieur 
modele MDP (Markov Decision Processes) qui sont des structures de données et des algorithmes permettant de modéliser et résoudre des problèmes où un agent interagit 
avec un environnement pour apprendre une politique optimale, en se basant sur des états, des actions, des transitions et des récompenses. Dont le QLearning fait partie.

3. Intégration des librairies : Après avoir intégré les librairies, j'ai examiné en détail les scripts pour identifier les classes nécessaires à mes IA.

4. Création d'un fournisseur : J'ai commencer a développé un fournisseur implémentant une interface pour exploiter le QLearning.

5. Compréhension de l'intégration : J'ai étudié le code de la librairie, consulté la documentation et utilisé ChatGPT pour clarifier certains concepts.

6. Finalisation du fournisseur : Après avoir compris l'intégration de la librairie, j'ai terminé la mise en place du fournisseur.

7. Développement de l'actor AI : J'ai créé une classe AI qui gère la logique du QLearning, laissant aux classes dérivées le soin d'implémenter leur propre logique.

# Entrainement
1. AI Chenille : Pour la chenille, j'ai créé une IA qui apprend à suivre le joueur. Pour son apprentissage, j'ai conçu une IA capable de se déplacer dans les 8 directions.
Ainsi, elle possède 8 états, chacun correspondant à une direction qu'elle peut prendre par rapport au joueur. Ensuite, je lui ai donné des récompenses si elle se déplace 
dans la bonne direction par rapport au joueur.

2. AI Mouche : Pour la mouche, j'ai souhaité développer une IA qui apprend à se déplacer dans des directions aléatoires, changeant à des intervalles de temps définis. 
Pour ce faire, j'ai intégré 8 états dans mon IA, et à un intervalle régulier, l'état de l'IA change. Par la suite, j'ai récompensé l'IA lorsqu'elle se déplaçait dans 
une direction précise pour chacun de ses états.

3. AI Boss : Le boss est une IA possédant deux états : un où il réfléchit et un autre où il exécute une action. Je lui ai intégré trois actions : une où il ne fait rien, 
une autre où il saute et, s'il réexécute cette action lors du saut, il se déplace vers le joueur, et enfin, une où il vomit une mouche. Les récompenses sont données de façon 
équivalente pour le vomissement et le saut, ce qui rend les actions du boss imprévisibles.

# Conclusion et retour d'experience (ce qui a fonctionne ou non, les lecons pour l'avenir)
L'expérience s'est globalement bien déroulée. Le principal défi a été l'importation de la librairie et de ses dépendances, ainsi que leur intégration dans le projet. 
Cette expérience m'a appris l'importance de bien comprendre l'architecture et les dépendances d'un projet.