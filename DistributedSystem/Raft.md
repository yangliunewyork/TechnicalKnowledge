# What is Raft

Raft is a consensus algorithm designed as an alternative to Paxos. It was meant to be more understandable than Paxos by means of separation of logic, but it is also formally proven safe and offers some additional features. Raft offers a generic way to distribute a __state machine__ across a cluster of computing systems, ensuring that each node in the cluster agrees upon the same series of state transitions. It has a number of open-source reference implementations, with full-spec implementations in Go, C++, Java, and Scala.

# Basics

Raft achieves consensus via an elected leader. A server in a raft cluster is either a leader, a candidate, or a follower. The leader is responsible for log replication to the followers. It regularly informs the followers of its existence by sending a heartbeat message. Each follower has a timeout (typically between 150 and 300 ms) in which it expects the heartbeat from the leader. The timeout is reset on receiving the heartbeat. If no heartbeat is received the follower changes its status to candidate and starts a leader election.

### Leader Election

A leader election is started by a candidate server. A server becomes a candidate if it receives no heartbeat from the leader within the timeout. It starts the election by increasing the term counter and sending a RequestVote message to all other servers. The other servers will vote for the first candidate that sends them a RequestVote message. A server will only vote once per term. If the candidate receives a message from a leader with a term number equal to or larger than the current term, then its election is defeated and the candidate changes into a follower. If a candidate receives a majority of votes, then it becomes the new leader. If neither happens, e.g., because of a split vote, then a new leader election is started after a timeout.

The timeout values of each server should be spread out within a reasonable interval. This should reduce the chance of a split vote because servers won't become candidates at the same time.

### Log Replication
The leader is responsible for the log replication. It accepts client requests. The requests are forwarded to the followers in AppendEntries messages. Once the leader receives confirmation from the majority of its followers the request is considered committed.
