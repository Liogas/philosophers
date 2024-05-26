# philosophers

## INFOS DERNIER GIT
- Manipulation du temps écoulée (chrono pour chaque philo lancé)

## EN COURS
- Manipulation du temps écoulée
- Mise en place de la routine d'un philo

## A FAIRE
- Affichage du message de changement de statut

## FINI
- Mettre en place les structures contenant les donnees du projet
- Parsing
- Creation des philos
- Création et mise en place des fourchettes

## FONCTIONS
- Memset
- Printf
- Malloc
- Free
- Write
- Usleep
- Gettimeofday
Sert a lire l'heure
int gettimeofday(struct timeval *tv, NULL)
La structure timeval contient deux membres : tv_sec(seconde), tv_usec(microsecondes)
Valeur de retour : 0(OK) -1(KO) errno utilisable
- Pthread_create
Creer un nouveau thread
int pthread_create(pthread_t *thread, pthread_attr_t *attr, void * (*start_routine) (void *), void *arg)
pthread_t : Identifiant du thread (unsigned long sous linux)
pthread_attr_t : Permet de changer la gestion ds threads
void * (*start_routine) (void *) : Fonction executee par le thread
void *arg : Argument utile pour la fonction
Valeur de retour : 0(OK) valeur non null(KO)
- Pthread_detach
- Pthread_join
Permet d'attendre la fin d'un thread en mettant en pause le thread appelant
int pthread_join(pthread_t th, void **thread_return)
pthread_t th : Identifiant du thread a attendre
void **thread_return : Valeur de retour de la fonction du thread th
Valeur de retour : 0(OK) valeur non null(KO)
- Pthread_mutex_lock
- Pthread_mutex_unlock'

## IMPORTANT
pour pouvoir utiliser les fonctions concernant les threads ajouter -lpthread et -D_REENTRANT

## THREAD
Un thread est une portion de code qui s'execute en meme temps que le main.