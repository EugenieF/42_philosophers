![42](img/42Project.png "42")

# PHILOSOPHERS

*🎯 Aim : learn the basics of threading a process*

[Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

### 📄 Subject
• Each philosopher should be a thread.
• There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.
• To prevent philosophers from duplicating forks, you should protect the forks state
with a mutex for each of them.

### ⭐ Bonus subject
• All the forks are put in the middle of the table.
• They have no states in memory but the number of available forks is represented by
a semaphore.
• Each philosopher should be a process. But the main process should not be a
philosopher.
