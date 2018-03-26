A __gossip protocol__ is a procedure or process of computer-computer communication that is based on the way social networks disseminate information or how epidemics spread. It is a communication protocol. Modern distributed systems often use gossip protocols to solve problems that might be difficult to solve in other ways, either because the underlying network has an inconvenient structure, is extremely large, or because gossip solutions are the most efficient ones available.

The term __epidemic protocol__ is sometimes used as a synonym for a gossip protocol, because gossip spreads information in a manner similar to the spread of a virus in a biological community.

### Gossip communication

The concept of gossip communication can be illustrated by the analogy of office workers spreading rumors. Let's say each hour the office workers congregate around the water cooler. Each employee pairs off with another, chosen at random, and shares the latest gossip. At the start of the day, Alice starts a new rumor: she comments to Bob that she believes that Charlie dyes his mustache. At the next meeting, Bob tells Dave, while Alice repeats the idea to Eve. After each water cooler rendezvous, the number of individuals who have heard the rumor roughly doubles (though this doesn't account for gossiping twice to the same person; perhaps Alice tries to tell the story to Frank, only to find that Frank already heard it from Dave). Computer systems typically implement this type of protocol with a form of random "peer selection": with a given frequency, each machine picks another machine at random and shares any hot rumors.

The power of gossip lies in the robust spread of information. Even if Dave had trouble understanding Bob, he will probably run into someone else soon and can learn the news that way.

Expressing these ideas in more technical terms, a gossip protocol is one that satisfies the following conditions:

* The core of the protocol involves periodic, pairwise, inter-process interactions.  
* The information exchanged during these interactions is of bounded size.  
* When agents interact, the state of at least one agent changes to reflect the state of the other.  
* Reliable communication is not assumed.  
* The frequency of the interactions is low compared to typical message latencies so that the protocol costs are negligible.  
* There is some form of randomness in the peer selection. Peers might be selected from the full set of nodes or from a smaller set of neighbors.  
* Due to the replication there is an implicit redundancy of the delivered information.  

### Gossip protocol types

