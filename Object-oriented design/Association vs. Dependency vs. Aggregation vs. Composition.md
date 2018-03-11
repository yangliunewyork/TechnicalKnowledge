https://nirajrules.wordpress.com/2011/07/15/association-vs-dependency-vs-aggregation-vs-composition/

__Association__ is _reference based relationship_ between two classes. Here a class A holds a class level reference to class B. Association can be represented by a line between these classes with an arrow indicating the navigation direction. In case arrow is on the both sides, association has bidirectional navigation.

<img src="https://nirajrules.files.wordpress.com/2011/07/association.png" height="100" witth="100">


```java
class Asset { ... }
class Player {
  Asset asset;
  public Player(Assest purchasedAsset) { ... } /*Set the asset via Constructor or a setter*/
}
```

__Dependency__ is often confused as Association. Dependency is normally created when you receive a reference to a class as part of a particular operation / method. _Dependency indicates that you may invoke one of the APIs of the received class reference and any modification to that class may break your class as well._ Dependency is represented by a dashed arrow starting from the dependent class to its dependency. Multiplicity normally doesn’t make sense on a Dependency.

<img src="https://nirajrules.files.wordpress.com/2011/07/dependency.png" height="100" witth="100">

```java
class Die { public void Roll() { ... } }
class Player
{
  public void TakeTurn(Die die) /*Look ma, I am dependent on Die and it's Roll method to do my work*/
  { die.Roll(); ... }
}
```

__Aggregation__ is same as association and is often seen as redundant relationship. A common perception is that aggregation represents one-to-many / many-to-many / part-whole relationships (i.e. higher multiplicity), which of course can be represented by via association too (hence the redundancy). As aggregation doesn’t convey anything more effective about a software design than an association, there is no separate UML representation for it (though some developers use a hollow diamond to indicate aggregation). You can give aggregation a miss unless you use it to convey something special.

<img src="https://nirajrules.files.wordpress.com/2011/07/aggregation.png" height="100" witth="100">

```java
class Asset { ... }
class Player {
  List assets;
  public void AddAsset(Asset newlyPurchasedAsset) { assets.Add(newlyPurchasedAssest); ... }
  ...
}
```

__Composition__ relates to instance creational responsibility. When class B is composed by class A, class A instance owns the creation or controls lifetime of instance of class B. Needless to say when class instance A instance is destructed (garbage collected), class B instance would meet the same fate. Composition is usually indicated by line connecting two classes with addition of a solid diamond at end of the class who owns the creational responsibility. It’s also a perceived wrong notion that composition is implemented as nested classes. Composition binds lifetime of a specific instance for a given class, while class itself may be accessible by other parts of the system.

<img src="https://nirajrules.files.wordpress.com/2011/07/composition.png" height="100" witth="100">

```java
public class Piece { ... }
public class Player
{
  Piece piece = new Piece(); /*Player owns the responsibility of creating the Piece*/
  ...
}
```
