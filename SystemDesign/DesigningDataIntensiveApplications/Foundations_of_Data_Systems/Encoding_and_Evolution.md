The notes comes from this book : https://www.amazon.com/Designing-Data-Intensive-Applications-Reliable-Maintainable/dp/1449373321 , one of the best in this field.

Applications inevitably change over time. Features are added or modified as new products are launched, user requirements become better understood, or business cir‐ cumstances change. In Chapter 1 we introduced the idea of evolvability: we should aim to build systems that make it easy to adapt to change.

In most cases, a change to an application’s features also requires a change to data that it stores: perhaps a new field or record type needs to be captured, or perhaps existing data needs to be presented in a new way.

The data models we discussed in Chapter 2 have different ways of coping with such change. Relational databases generally assume that all data in the database conforms to one schema: although that schema can be changed (through schema migrations; i.e., ALTER statements), there is exactly one schema in force at any one point in time. By contrast, schema-on-read (“schemaless”) databases don’t enforce a schema, so the database can contain a mixture of older and newer data formats written at different times.

When a data format or schema changes, a corresponding change to application code often needs to happen (for example, you add a new field to a record, and the applica‐ tion code starts reading and writing that field). However, in a large application, code changes often cannot happen instantaneously:

* With server-side applications you may want to perform a __rolling upgrade__ (also known as a __staged rollout__), deploying the new version to a few nodes at a time, checking whether the new version is running smoothly, and gradually working your way through all the nodes. This allows new versions to be deployed without service downtime, and thus encourages more frequent releases and better evolva‐ bility.
* With client-side applications you’re at the mercy of the user, who may not install the update for some time.

This means that old and new versions of the code, and old and new data formats, may potentially all coexist in the system at the same time. In order for the system to continue running smoothly, we need to maintain compatibility in both directions:

```
Backward compatibility : Newer code can read data that was written by older code.
Forward compatibility : Older code can read data that was written by newer code.
```

Backward compatibility is normally not hard to achieve: as author of the newer code, you know the format of data written by older code, and so you can explicitly handle it (if necessary by simply keeping the old code to read the old data). Forward compati‐ bility can be trickier, because it requires older code to ignore additions made by a newer version of the code.

In this chapter we will look at several formats for encoding data, including JSON, XML, Protocol Buffers, Thrift, and Avro. In particular, we will look at how they han‐ dle schema changes and how they support systems where old and new data and code need to coexist. We will then discuss how those formats are used for data storage and for communication: in web services, Representational State Transfer (REST), and remote procedure calls (RPC), as well as message-passing systems such as actors and message queues.

## Formats for Encoding Data
