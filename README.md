#LAN Party

Faculty of Automatics  Control and Computer Science organises a LAN Party
each semester with the help of LSAC. At this event participate every 
student who wants to test they're abilities in a certain game. It is 
desired a software implementation which automates this process.

Tasks:

1)There will be created a list in a external folder "date.in".

2)The teams with the lowest score will be deleted from the list so 
it will remain a number of n teams where n is a power of two. 

Note: If two teams have the same score the one that gets deleted is the one
which immediatly follows in the list. If the one that should be deleted
is the team from the head of the list , the list will have a new head.

3)Structures to be implemented:

-Queue for matches between teams.

-The mathces will take place in the list order.

-Two stacks , one for winners , one for losers.

-The loser stack will be deleted

-The winner stack will be inserted in the match queue and the steps will
be repeated

-The procces will take place until eight teams remain.

4)In a Binary Search Tree will be created a rank acording to team scores.
