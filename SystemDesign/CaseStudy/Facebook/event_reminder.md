```
Scenario:
用户注册，登陆功能
用户创建event，邀请好友参加event
到了event时间，系统通知user

Service
User Service:
Register()
Login(username, password)

Event Service:
AddEvent(UserId)
Remind(EventID)
LookupEvent(UserId)

Storage: 
以sql为例：
User Table(UserId, username, email)
Event Table(EventId, event_happen_time, created_by_userid, event_address, notification_time)
Invitation Table(EventId, userId)

用户创建event时，event Table插入一条新纪录。Notification_time 是到了这个时间，系统通知created_by_userid。
当用户A邀请B,C 参加event，Invitation Table插入两条记录：(userBId, eventId3) (UserCId, eventId3).

Optimized：
首先，如果需要通知的event很多，怎么处理？
到了notification_time 通知用户，是不是可以保存这个东西在内存里，然后排序，到时间在通过email方式通知用户？
还有，如果一个用户创建那种每星期1下午3点都有的event，应该怎么建table？
```

这是一个典型的 Producer Consumer 模型。除了 Event Table 以外，我们需要一个 Notification Table。这个 Notification Table 记录的就是需要在什么时间，通知谁，什么事情，这一次性通知的，还是循环通知，如果是循环通知，那么循环规则是什么。 Notification Table 按照需要通知的时间进行排序。

先说如果 event少的 work solution 是什么：用一个进程，每隔 5s 扫一下这个table，不是线性扫描，而是 select 一下有哪些 Notification 的时间 小于 了当前时间。然后把需要通知的一个个通知。

如果需要通知的event很多，怎么处理？
一个人干不完的活，多个人干。如果通知特别多的话，我们就 sharding 呗。如果我们不需要支持删除一条 Notication 的话，我们甚至可以随意分给多个机器就好了。但这个问题中，不容易发现的是，如果我取关了一个 Event，需要把我的 Notification 删除。所以我们 sharding 的时候，应该按照被提醒的用户的 user_id 进行 sharding。这样才能在需要删除的时候，还能再找回来。

Sharding 完以后，每个负责发提醒任务的进程就专门负责一个 sharding block 里的数据的提醒。

如果一个用户创建那种每星期1下午3点都有的event，应该怎么建table？
在前面的 Notification Table 的定义中，我已经给出答案了。基本思想就是，一条 notification 记录着下一次需要提醒的时间是什么，然后当这个 notification 被提醒之后，如果是一次性的，就直接扔掉了，如果是循环的，那么就根据循环规则计算出下一次需要提醒的时间，然后重新丢回 Notification Table 中。

