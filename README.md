![42](img/42Project.png "42")

# PHILOSOPHERS

*🎯 Aim : learn the basics of threading a process*

[Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

## 📄 Subject rules
- One or more philosophers sit at a round table.
-  The philosophers alternatively eat, think, or sleep.
-  There are as many forks as philosophers.
-  A philosopher takes their right and their left forks to eat, one in each hand.
-  When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that philosophers should avoid dying!

### Mandatory rules
- Each philosopher should be a __thread__.
- There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks state
with a __mutex__ for each of them.

### Bonus rules
- All the forks are put in the middle of the table.
- They have no states in memory but the number of available forks is represented by
a __semaphore__.
- Each philosopher should be a __process__. But the main _process should not be a
philosopher.
