#include "philophers.h"

int	is_thinking(t_philosopher *philosopher)
{
	return (philosopher->state == THINKING);
}

int	is_eating(t_philosopher *philosopher)
{
	return (philosopher->state == EATING);
}

int	is_sleeping(t_philosopher *philosopher)
{
	return (philosopher->state == SLEEPING);
}

int	is_dead(t_philosopher *philosopher)
{
	return (philosopher->state == DEAD);
}
