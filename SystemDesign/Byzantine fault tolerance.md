### Byzantine Generals' Problem

Byzantine refers to the Byzantine Generals' Problem, an agreement problem, (described by Leslie Lamport, Robert Shostak and Marshall Pease in their 1982 paper, "The Byzantine Generals Problem"), in which a group of generals, each commanding a portion of the Byzantine army, encircle a city. These generals wish to formulate a plan for attacking the city. In its simplest form, the generals must only decide whether to attack or retreat. Some generals may prefer to attack, while others prefer to retreat. The important thing is that every general agrees on a common decision, for a halfhearted attack by a few generals would become a rout and be worse than a coordinated attack or a coordinated retreat.

The problem is complicated by the presence of traitorous generals who may not only cast a vote for a suboptimal strategy, they may do so selectively. For instance, if nine generals are voting, four of whom support attacking while four others are in favor of retreat, the ninth general may send a vote of retreat to those generals in favor of retreat, and a vote of attack to the rest. Those who received a retreat vote from the ninth general will retreat, while the rest will attack (which may not go well for the attackers). The problem is complicated further by the generals being physically separated and having to send their votes via messengers who may fail to deliver votes or may forge false votes.

Byzantine fault tolerance can be achieved if the loyal (non-faulty) generals have a majority agreement on their strategy. Note that there can be a default vote value given to missing messages. For example, missing messages can be given the value <Null>. Further, if the agreement is that the <Null> votes are in the majority, a pre-assigned default strategy can be used (e.g., retreat).[citation needed]

The typical mapping of this story onto computer systems is that the computers are the generals and their digital communication system links are the messengers. Although the problem is formulated in the analogy as a decision-making and security problem, in electronics, it cannot be solved simply by cryptographic digital signatures, because failures like incorrect voltages can propagate through the encryption process. Thus, a component may appear functioning to one component and faulty to another, which prevents forming a consensus whether the component is faulty or not.

### Detail description of Byzantine Generals' Problem

On July 5th 1982, Leslie Lamport (initial LaTeX developer, Microsoft Researcher and winner of the 2013 Turing Award), Robert Shostak and Marshall Pease published a paper named The Byzantine Generals' Problem.

The group devised a thought experiment for an __abstract agreement problem__.

They imagined that several divisions of the Byzantine army are camped outside an enemy city, each division commanded by its own general. The generals can communicate with one another only by messenger. After observing the enemy, they must decide upon a common plan of action.

In its simplest form, the generals must only decide whether to attack or retreat. Some generals may prefer to attack, while others prefer to retreat. The important thing is that every general agrees on a common decision, for a half hearted attack by a few generals would be worse than a coordinated attack or a coordinated retreat.

Since it's impossible to know which generals are traitors trying to prevent the loyal generals from reaching agreement, the generals must have an algorithm to guarantee that all loyal generals decide upon the same plan of action and that a small number of traitors cannot cause the loyal generals to adopt a bad plan.

#### The Traitorous General

If nine generals are voting, four of whom support attacking while four others are in favor of retreat, the ninth general (traitorous general) may send a vote of retreat to those generals in favor of retreat, and a vote of attack to the rest. Those who received a retreat vote from the ninth general will retreat, while the rest will attack.

<img src="https://blog.cdemi.io/content/images/2017/06/The-Traitorous-General.png" height="500" width="800">

#### The Traitorous Messenger

To make matters worse, the generals are physically separated and have to send their votes via messengers who may fail to deliver votes or may forge false votes (traitorous messenger).

<img src="https://blog.cdemi.io/content/images/2017/06/The-Traitorous-Messenger.png" height="500" width="800">

#### What is Byzantine Failure?

__The typical mapping of this story onto computer systems is that the computers are the generals and their digital communication system links are the messengers.__

Simply put, a Byzantine Fault is a fault that presents different symptoms to different observers. Similarly, a Byzantine Failure is the loss of a system component due to a Byzantine Fault in a distributed system that requires consensus.

So it stands to reason that the objective of a Byzantine Fault Tolerant system is to be able to defend against Byzantine failures.

A correctly implemented Byzantine Fault Tolerant system should be able to still provide service, assuming that the majority of the components are still healthy.

#### Achieving Byzantine Fault Tolerance

Several system architectures were designed that implement Byzantine Fault Tolerance. Implementations are very specific to their use case. Nonetheless, there are 2 prominent solutions that these systems may end up implementing:

* __Unforgeable message signatures.__ This may be achieved by using Public-Key Cryptography (see Introduction to the Diffie-Hellman Key Exchange).
* __Atomic Broadcasts.__ If the message system is such that the command is transmitted simultaneously to all participants, then A cannot send a different message to C and B.

These solutions are not mutually exclusive, so systems that need to be highly byzantine fault tolerant usually end up implementing a variation which includes both.

#### Byzantine Fault Tolerance in Practice

* Bitcoin : Bitcoin, the peer-to-peer cryptocurrency that's based on a blockchain, is Byzantine Fault Tolerant. The bitcoin network works in parallel to generate a chain of Hashcash style proof-of-work (also known as CPU Cost Function, Client Puzzle, Computational Puzzle or CPU Pricing Function). This proof-of-work chain is the key to overcome Byzantine failures and to reach a coherent global view of the system state.  
* Aircraft : The Boeing 777 Aircraft Information Management System and the flight control system use Byzantine Fault Tolerance. Because these are real-time systems, their Byzantine fault tolerance solutions must have very low latency. In fact, Boeing states that SAFEbus, a standard backplane bus for commercial avionics, can achieve Byzantine fault tolerance on the order of a microsecond of added latency.

# What is Byzantine fault tolerance?

__Byzantine fault tolerance (BFT)__ is the dependability of a fault-tolerant computer system, particularly distributed computing systems, where components may fail and there is imperfect information on whether a component is failed. In a "Byzantine failure", a component such as a server can inconsistently appear both failed and functioning to failure-detection systems, presenting different symptoms to different observers.

It is difficult for the other components to declare it failed and shut it out of the network, because they need to first reach a consensus regarding which component is failed in the first place. The term is derived from the __Byzantine Generals' Problem__, where actors must agree on a concerted strategy to avoid catastrophic system failure, but some of the actors are unreliable. Byzantine fault tolerance has been also referred to with the phrases interactive consistency or source congruency, error avalanche, Byzantine agreement problem, Byzantine generals problem, and Byzantine failure.

### Background

A Byzantine fault is any fault presenting different symptoms to different observers. A Byzantine failure is the loss of a system service due to a Byzantine fault in systems that require consensus.

The objective of Byzantine fault tolerance is to be able to defend against Byzantine failures, in which components of a system fail with symptoms that prevent some components of the system from reaching agreement among themselves, where such agreement is needed for the correct operation of the system. Correctly functioning components of a Byzantine fault tolerant system will be able to provide the system's service, assuming there are not too many faulty components.

Byzantine failures are considered the most general and most difficult class of failures among the __failure modes__. The so-called fail-stop failure mode occupies the simplest end of the spectrum. Whereas fail-stop failure model simply means that the only way to fail is a node crash, detected by other nodes, Byzantine failures imply no restrictions, which means that the failed node can generate arbitrary data, pretending to be a correct one. Thus, Byzantine failures can confuse failure detection systems, which makes fault tolerance difficult. Despite the analogy, a Byzantine failure is not necessarily a security problem involving hostile human interference: it can arise purely from electrical faults.


### Early solutions

Several solutions were described by Lamport, Shostak, and Pease in 1982. They began by noting that the Generals' Problem can be reduced to solving a "Commander and Lieutenants" problem where loyal Lieutenants must all act in unison and that their action must correspond to what the Commander ordered in the case that the Commander is loyal.

* One solution considers scenarios in which messages may be forged, but which will be Byzantine-fault-tolerant as long as the number of traitorous generals does not equal or exceed one third of the generals. The impossibility of dealing with one-third or more traitors ultimately reduces to proving that the one Commander and two Lieutenants problem cannot be solved, if the Commander is traitorous. To see this, suppose we have a traitorous Commander A, and two Lieutenants, B and C: when A tells B to attack and C to retreat, and B and C send messages to each other, forwarding A's message, neither B nor C can figure out who is the traitor, since it is not necessarily A—another Lieutenant could have forged the message purportedly from A. It can be shown that if n is the number of generals in total, and t is the number of traitors in that n, then there are solutions to the problem only when n > 3t and the communication is synchronous (bounded delay).
* A second solution requires unforgeable message signatures. For security-critical systems, digital signatures (in modern computer systems, this may be achieved in practice using public-key cryptography) can provide Byzantine fault tolerance in the presence of an arbitrary number of traitorous generals. However, for safety-critical systems, simple error detecting codes, such as CRCs, provide weaker but often sufficient coverage at a much lower cost. This is true for both Byzantine and non-Byzantine faults. Thus, cryptographic digital signature methods are not a good choice for safety-critical systems, unless there is also a specific security threat as well. While error detecting codes, such as CRCs, are better than cryptographic techniques, neither provide adequate coverage for active electronics in safety-critical systems. This is illustrated by the Schrödinger CRC scenario where a CRC-protected message with a single Byzantine faulty bit presents different data to different observers and each observer sees a valid CRC.[3][4]
* Also presented is a variation on the first two solutions allowing Byzantine-fault-tolerant behavior in some situations where not all generals can communicate directly with each other.


