```
就是语言的国际化。
1, 发一条post可以变成多种语言。
2, 网页上的很多字符内容需要根据用户所处的地区来用当地语言显示，怎么实现这个功能。

Service:
PostService
CreatePost(LanguageId)
TranslateService
Translate(FromLanguageId, ToLanguageId)

Storage:
PostTable(PostId, Content)
```

1、发一条post变成多个语言，这个根据用户的关注数量进行不同的区分对待：如果用户是明星，那么提前翻译好所有语言的版本的post存在缓存里面；不然的话就等到有人获取的时候再当场翻译（可以不在服务器端做，提供一个transalte service，让用户的浏览器去调用api翻译，减轻服务器压力）。
2.把所有的翻译完的内容都存在数据库中并缓存，这样当用户要看的时候直接从缓存拿翻译好的内容就可以了。
3. 考虑按照地区去sharding。
