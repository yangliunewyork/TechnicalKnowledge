__Single sign-on (SSO)__ is a property of access control of multiple related, yet independent, software systems. With this property, a user logs in with a single ID and password to gain access to a connected system or systems without using different usernames or passwords, or in some configurations seamlessly sign on at each system. This is typically accomplished using the __Lightweight Directory Access Protocol (LDAP)__ and stored LDAP databases on (directory) servers. A simple version of single sign-on can be achieved over IP networks using cookies but only if the sites share a common DNS parent domain.

For clarity, it is best to refer to systems requiring authentication for each application but using the same credentials from a directory server as Directory Server Authentication and systems where a single authentication provides access to multiple applications by passing the authentication token seamlessly to configured applications as Single Sign-On.

Conversely, single sign-off is the property whereby a single action of signing out terminates access to multiple software systems.

As different applications and resources support different authentication mechanisms, single sign-on must internally store the credentials used for initial authentication and translate them to the credentials required for the different mechanisms.

Other shared authentication schemes such as OpenID, and OpenID Connect offer other services that may require users to make choices during a sign-on to a resource, but can be configured for single sign-on if those other services (such as user consent) are disabled. An increasing number of federated social logons, like Facebook Connect do require the user to enter consent choices at first registration with a new resource and so are not always single sign-on in the strictest sense. 

### Benefits

Benefits of using single sign-on include:

* Mitigate risk for access to 3rd-party sites (user passwords not stored or managed externally)
* Reduce password fatigue from different user name and password combinations
* Reduce time spent re-entering passwords for the same identity
* Reduce IT costs due to lower number of IT help desk calls about passwords

SSO shares centralized authentication servers that all other applications and systems use for authentication purposes and combines this with techniques to ensure that users do not have to actively enter their credentials more than once. 

> Password fatigue is the feeling experienced by many people who are required to remember an excessive number of passwords as part of their daily routine, such as to logon to a computer at work, undo a bicycle lock or conduct banking from an automated teller machine (ATM). The concept is also known as password chaos or more broadly as identity chaos.

单点登录（Single Sign On），简称为 SSO，是目前比较流行的企业业务整合的解决方案之一。SSO的定义是在多个应用系统中，用户只需要登录一次就可以访问所有相互信任的应用系统。
较大的企业内部，一般都有很多的业务支持系统为其提供相应的管理和IT服 务。例如财务系统为财务人员提供财务的管理、计算和报表服务；人事系统为人事部门提供全公司人员的维护服务；各种业务系统为公司内部不同的业务提供不同的 服务等等。这些系统的目的都是让计算机来进行复杂繁琐的计算工作，来替代人力的手工劳动，提高工作效率和质量。这些不同的系统往往是在不同的时期建设起来 的，运行在不同的平台上；也许是由不同厂商开发，使用了各种不同的技术和标准。如果举例说国内一著名的IT公司（名字隐去），内部共有60多个业务系统，这些系统包括两个不同版本的SAP的ERP系统，12个不同类型和版本的数据库系统，8个不同类型和版本的操作系统，以及使用了3种不同的防火墙技术，还有数十种互相不能兼容的协议和标准，你相信吗？不要怀疑，这种情况其实非常普遍。每一个应用系统在运行了数年以后，都会成为不可替换的企业IT架构的一部分，如下图所示。
随 着企业的发展，业务系统的数量在不断的增加，老的系统却不能轻易的替换，这会带来很多的开销。其一是管理上的开销，需要维护的系统越来越多。很多系统的数 据是相互冗余和重复的，数据的不一致性会给管理工作带来很大的压力。业务和业务之间的相关性也越来越大，例如公司的计费系统和财务系统，财务系统和人事系 统之间都不可避免的有着密切的关系。
为了降低管理的消耗，最大限度的重用已有投资的系统，很多企业都在进行着企业应用集成（EAI）。 企业应用集成可以在不同层面上进行：例如在数据存储层面上的“数据大集中”，在传输层面上的“通用数据交换平台”，在应用层面上的“业务流程整合”，和用 户界面上的“通用企业门户”等等。事实上，还用一个层面上的集成变得越来越重要，那就是“身份认证”的整合，也就是“单点登录”。
通常来说，每个单独的系统都会有自己的安全体系和身份认证系统。整合以前，进入每个系统都需要进行登录，这样的局面不仅给管理上带来了很大的困难，在安全方面也埋下了重大的隐患。下面是一些著名的调查公司显示的统计数据：

```
* 用户每天平均 16 分钟花在身份验证任务上 - 资料来源： IDS
* 频繁的 IT 用户平均有 21 个密码 - 资料来源： NTA Monitor Password Survey
* 9% 的人写下了其密码，而 67% 的人很少改变它们
* 每 79 秒出现一起身份被窃事件 - 资料来源：National Small Business Travel Assoc
* 全球欺骗损失每年约 12B - 资料来源：Comm Fraud Control Assoc
* 到 2007 年，身份管理市场将成倍增长至 $4.5B - 资料来源：IDS
```

另外，使用“单点登录”还是SOA时代的需求之一。在面向服务的架构中，服务和服务之间，程序和程序之间的通讯大量存在，服务之间的安全认证是SOA应用的难点之一，应此建立“单点登录”的系统体系能够大大简化SOA的安全问题，提高服务之间的合作效率。


 

### Criticism

The term reduced sign-on (RSO) has been used by some to reflect the fact that single sign-on is impractical in addressing the need for different levels of secure access in the enterprise, and as such more than one authentication server may be necessary.

As single sign-on provides access to many resources once the user is initially authenticated ("keys to the castle"), it increases the negative impact in case the credentials are available to other people and misused. Therefore, single sign-on requires an increased focus on the protection of the user credentials, and should ideally be combined with strong authentication methods like smart cards and one-time password tokens.

Single sign-on also makes the authentication systems highly critical; a loss of their availability can result in denial of access to all systems unified under the SSO. SSO can be configured with session failover capabilities in order to maintain the system operation.[6] Nonetheless, the risk of system failure may make single sign-on undesirable for systems to which access must be guaranteed at all times, such as security or plant-floor systems.

Furthermore, the use of single-sign-on techniques utilizing social networking services such as Facebook may render third party websites unusable within libraries, schools, or workplaces that block social media sites for productivity reasons. It can also cause difficulties in countries with active censorship regimes, such as China and its "Golden Shield Project," where the third party website may not be actively censored, but is effectively blocked if a user's social login is blocked.




