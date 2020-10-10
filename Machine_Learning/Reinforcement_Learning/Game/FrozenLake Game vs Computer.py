import gym
import numpy as np
import matplotlib.pyplot as plt
from gym.envs.registration import register
import readchar
LEFT = 0
DOWN = 1
RIGHT = 2
UP = 3

arrow_keys = {
    '\x1b[A': UP,
    '\x1b[B': DOWN,
    '\x1b[C': RIGHT,
    '\x1b[D': LEFT}
register(
    id='FrozenLake-v3',
    entry_point='gym.envs.toy_text:FrozenLakeEnv',
    kwargs={'map_name':'4x4' ,'is_slippery':False}
    )
env=gym.make('FrozenLake-v3')


Q=np.zeros([env.observation_space.n,env.action_space.n])
dis=.99
# num_episodes=2000

rList=[]

i=0
# for i in range(num_episodes):
while True:
    env.render()
    p_done=False
    while not p_done:
        key = readchar.readkey()
        if key not in arrow_keys.keys():
            print("Game aborted!")
            continue
        p_action = arrow_keys[key]
        p_state, p_reward, p_done, p_info = env.step(p_action)
        env.render()  # Show the board after action
        print("State: ", p_state, "Action: ", p_action,
              "Reward: ", p_reward, "Info: ", p_info)

        if p_done:
            if p_reward == 1:
                print('You Win')

            print("Finished with reward", p_reward)
            break

    done = False

    state = env.reset()
    print('COMPUTER TURN')
    while not done:


        env.render()


        i+=1
        e= 1./((i//100)+1)  # Decay E-greedy

        if np.random.rand(1) < e:
            action=env.action_space.sample() #Choose Randomly
        else:
            action=np.argmax(Q[state,:])


        new_state,reward,done,_=env.step(action)
        if done:
            if reward ==0:
                print('Computer Die')
                break
            else:
                print('Computer Win')
                break
        env.render()

        Q[state,action]=reward+dis*np.max(Q[new_state,:])

        state=new_state

        input('Any Key to next')



