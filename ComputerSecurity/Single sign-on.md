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

### Criticism

The term reduced sign-on (RSO) has been used by some to reflect the fact that single sign-on is impractical in addressing the need for different levels of secure access in the enterprise, and as such more than one authentication server may be necessary.

As single sign-on provides access to many resources once the user is initially authenticated ("keys to the castle"), it increases the negative impact in case the credentials are available to other people and misused. Therefore, single sign-on requires an increased focus on the protection of the user credentials, and should ideally be combined with strong authentication methods like smart cards and one-time password tokens.

Single sign-on also makes the authentication systems highly critical; a loss of their availability can result in denial of access to all systems unified under the SSO. SSO can be configured with session failover capabilities in order to maintain the system operation.[6] Nonetheless, the risk of system failure may make single sign-on undesirable for systems to which access must be guaranteed at all times, such as security or plant-floor systems.

Furthermore, the use of single-sign-on techniques utilizing social networking services such as Facebook may render third party websites unusable within libraries, schools, or workplaces that block social media sites for productivity reasons. It can also cause difficulties in countries with active censorship regimes, such as China and its "Golden Shield Project," where the third party website may not be actively censored, but is effectively blocked if a user's social login is blocked.

