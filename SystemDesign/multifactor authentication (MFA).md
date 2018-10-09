https://searchsecurity.techtarget.com/definition/multifactor-authentication-MFA . 

Multifactor authentication (MFA) is a security system that requires more than one method of authentication from independent categories of credentials to verify the user’s identity for a login or other transaction.

Multifactor authentication combines two or more independent credentials: what the user knows (password), what the user has (security token) and what the user is (biometric verification). The goal of MFA is to create a layered defense and make it more difficult for an unauthorized person to access a target such as a physical location, computing device, network or database. If one factor is compromised or broken, the attacker still has at least one more barrier to breach before successfully breaking into the target.

Typical MFA scenarios include:

* Swiping a card and entering a PIN.  
* Logging into a website and being requested to enter an additional one-time password (OTP) that the website's authentication server sends to the requester's phone or email address.  
* Downloading a VPN client with a valid digital certificate and logging into the VPN before being granted access to a network.
* Swiping a card, scanning a fingerprint and answering a security question.  
* Attaching a USB hardware token to a desktop that generates a one-time passcode and using the one-time passcode to log into a VPN client.  

### Background

One of the largest problems with traditional user ID and password login is the need to maintain a password database. Whether encrypted or not, if the database is captured it provides an attacker with a source to verify his guesses at speeds limited only by his hardware resources. Given enough time, a captured password database will fall.

As processing speeds of CPUs  have increased, brute force attacks have become a real threat. Further developments like GPGPU password cracking and rainbow tables have provided similar advantages for attackers. GPGPU cracking, for example, can produce more than 500,000,000 passwords per second, even on lower end gaming hardware. Depending on the particular software, rainbow tables can be used to crack 14-character alphanumeric passwords in about 160 seconds. Now purpose-built FPGA cards, like those used by security agencies, offer ten times that performance at a minuscule fraction of GPU power draw. A password database alone doesn't stand a chance against such methods when it is a real target of interest.

In the past, MFA systems typically relied upon two-factor authentication. Increasingly, vendors are using the label "multifactor" to describe any authentication scheme that requires more than one identity credential.

### Authentication factors

An authentication factor is a category of credential used for identity verification. For MFA, each additional factor is intended to increase the assurance that an entity involved in some kind of communication or requesting access to some system is who, or what, they are declared to be. The three most common categories are often described as something you know (the knowledge factor), something you have (the possession factor) and something you are (the inherence factor).

Knowledge factors – information that a user must be able to provide in order to log in. User names or IDs, passwords, PINs and the answers to secret questions all fall under this category. See also: knowledge-based authentication (KBA)

Possession factors - anything a user must have in their possession in order to log in, such as a security token, a one-time password (OTP) token, a key fob, an employee ID card or a phone’s SIM card. For mobile authentication, a smartphone often provides the possession factor, in conjunction with an OTP app.

Inherence factors - any biological traits the user has that are confirmed for login. This category includes the scope of biometric authentication  methods such as retina scans, iris scans fingerprint scans, finger vein scans, facial recognition, voice recognition, hand geometry, even earlobe geometry.

Location factors – the user’s current location is often suggested as a fourth factor for authentication. Again, the ubiquity of smartphones can help ease the authentication burden here: Users typically carry their phones and most smartphones have a GPS device, enabling reasonable surety confirmation of the login location.

Time factors – Current time is also sometimes considered a fourth factor for authentication or alternatively a fifth factor. Verification of employee IDs against work schedules could prevent some kinds of user account hijacking attacks. A bank customer can't physically use their ATM card in America, for example, and then in Russia 15 minutes later. These kinds of logical locks could prevent many cases of online bank fraud.

### Multifactor authentication technologies:

* Security tokens: Small hardware devices that the owner carries to authorize access to a network service. The device may be in the form of a smart card or may be embedded in an easily-carried object such as a key fob or USB drive. Hardware tokens provide the possession factor for multifactor authentication. Software-based tokens are becoming more common than hardware devices.  
* Soft tokens: Software-based security token applications that generate a single-use login PIN. Soft tokens are often used for multifactor mobile authentication, in which the device itself – such as a smartphone – provides the possession factor.  
* Mobile authentication: Variations include: SMS messages and phone calls sent to a user as an out-of-band method, smartphone OTP apps, SIM cards and smartcards with stored authentication data.  
* Biometric authentication methods such as retina scans, iris scans fingerprint scans, finger vein scans, facial recognition, voice recognition, hand geometry and even earlobe geometry.  
* GPS smartphones can also provide location as an authentication factor with this on board hardware.  
* Employee ID and customer cards, including magnetic strip and smartcards.  

