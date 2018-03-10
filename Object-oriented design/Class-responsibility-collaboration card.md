__Class-responsibility-collaboration (CRC) cards__ are a brainstorming tool used in the design of object-oriented software. They were originally proposed by Ward Cunningham and Kent Beck as a teaching tool, but are also popular among expert designers and recommended by __extreme programming__ supporters. Martin Fowler has described CRC cards as a viable alternative to UML sequence diagram to design the dynamics of object interaction and collaboration.

<img src="https://www.safaribooksonline.com/library/view/pattern-oriented-software-architecture/9781119963998/images/ch012-f008.jpg" height = "300" width = "500">

CRC cards are usually created from index cards. Members of a brainstorming session will write up one CRC card for each relevant class/object of their design. The card is partitioned into three areas:

* On top of the card, the class name
* On the left, the responsibilities of the class
* On the right, collaborators (other classes) with which this class interacts to fulfill its responsibilities

Using a small card keeps the complexity of the design at a minimum. It focuses designers on the essentials of the class and prevents them from getting into its details and implementation at a time when such detail is probably counter-productive. It also discourages giving the class too many responsibilities. Because the cards are portable, they can easily be laid out on a table and re-arranged while discussing a design.
