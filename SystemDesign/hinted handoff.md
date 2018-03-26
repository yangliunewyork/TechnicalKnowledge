### What does "hinted handoff" refer to in database systems?

This term is usually a reference to section 4.6 of https://www.allthingsdistributed.com/files/amazon-dynamo-sosp2007.pdf -- Amazon's Dynamo.

It only makes sense in distributed databases which have some element of eventual consistency in their operational model, and it is closely tied to another term in that paper, "sloppy quorum."

If the replica set for a given item X is nodes A, B, and C, but A is transiently unreachable, sloppy quorum allows a write of X to be sent to B, C, and D instead and considered successful once a quorum of that "sloppy" replica set is successful in acknowledging it. The write to D would be stored with a "hint" that it should ideally have been sent to A. Once A is detected to have recovered, D would attempt to hand off that data or operations. This "hinted handoff" is one of the mechanisms by which such a database can maintain expected levels of availability and durability across failure states.
