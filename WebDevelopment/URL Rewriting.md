### What is "URL Rewriting"?

Most dynamic sites include variables in their URLs that tell the site what information to show the user. Typically, this gives URLs like the following, telling the relevant script on a site to load product number 7.

```
http://www.pets.com/show_a_product.php?product_id=7
```

The problems with this kind of URL structure are that the URL is not at all memorable. It's difficult to read out over the phone (you'd be surprised how many people pass URLs this way). Search engines and users alike get no useful information about the content of a page from that URL. You can't tell from that URL that that page allows you to buy a Norwegian Blue Parrot (lovely plumage). It's a fairly standard URL - the sort you'd get by default from most CMSes. Compare that to this URL:

```
http://www.pets.com/products/7/
```

Clearly a much cleaner and shorter URL. It's much easier to remember, and vastly easier to read out. That said, it doesn't exactly tellanyone what it refers to. But we can do more:

```
http://www.pets.com/parrots/norwegian-blue/
```

Now we're getting somewhere. You can tell from the URL, even when it's taken out of context, what you're likely to find on that page. Search engines can split that URL into words (hyphens in URLs are treated as spaces by search engines, whereas underscores are not), and they can use that information to better determine the content of the page. It's an easy URL to remember and to pass to another person.

Unfortunately, the last URL cannot be easily understood by a server without some work on our part. When a request is made for that URL, the server needs to work out how to process that URL so that it knows what to send back to the user. URL rewriting is the technique used to "translate" a URL like the last one into something the server can understand.

UrlRewrite就是我们通常说的地址重写，用户得到的全部都是经过处理后的URL地址

主要优点:  
1. 提高安全性，可以有效的避免一些参数名、ID等完全暴露在用户面前，如果用户随便乱输的话，不符合规则的话直接会返回个404或错误页面，这比直接返回500或一大堆服务器错误信息要好的多  
2. 美化URL，去除了那些比如*.do之类的后缀名、长长的参数串等，可以自己组织精简更能反映访问模块内容的URL  
3. 更有利于搜索引擎的收入，通过对URL的一些优化，可以使搜索引擎更好的识别与收录网站的信息  

URL重写就是首先获得一个进入的URL请求然后把它重新写成网站可以处理的另一个URL的过程。举个例子来说，如果通过浏览器进来的URL是“UserProfile.aspx?ID=1”那么它可以被重写成 “UserProfile/1.aspx”，这样的URL，这样的网址可以更好的被网站所阅读。

如果浏览器不支持Cookie或用户阻止了所有Cookie，可以把会话ID附加在HTML页面中所有的URL上，这些页面作为响应发送给客户。这样，当用户单击URL时，会话ID被自动作为请求行的一部分而不是作为头行发送回服务器。这种方法称为URL重写(URL rewriting)。

一般来说，URL重写是支持会话的非常健壮的方法。在不能确定浏览器是否支持Cookie的情况下应该使用这种方法。然而，使用URL重写应该注意下面几点：  
1. 如果使用URL重写，应该在应用程序的所有页面中，对所有的URL编码，包括所有的超链接和表单的action属性值。  
2. 应用程序的所有的页面都应该是动态的。因为不同的用户具有不同的会话ID，因此在静态HTML页面中无法在URL上附加会话ID。  
3. 所有静态的HTML页面必须通过Servlet运行，在它将页面发送给客户时会重写URL。  

### Platforms and Tools

http://httpd.apache.org/docs/2.0/misc/rewriteguide.html

