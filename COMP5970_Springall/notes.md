`Security Mindset` - is a mental model that views situations from an attacker's
perspective to proactively identify concerns

__Requires__
* Understanding of offensive techniques
* Exploration of problem space
* Rational paranoia

`Intelligent Actor` - person, group, or organization not restricted by expectation

__Has Own__
* Capabilities
* Motivations
* Intentions

`Threat Modeling` - a systematic approach to analyzing and understanding potential
threats
* What are you trying to defend
* Who are you defending against
* What are you willing to trade

`Asset Identification` - is gaining awareness of what should be protected and where
it is located

__Requires__
* Exploration of system
* Critical Thinking
* Impact analysis

__Actors by Intent__
* `Black Hat` - malicious and/or unethical
* `White Hat` - Ethical and/or cooperating
* `Grey Hat` - :shrug:

__Attackers by Ability__
* Domain knowledge
* Available resources
* Access to vulnerabilities

__Low Capabilities (Skiddies)__
* Little to zero knowledge
* Little to zero resources
* "Point-and-Click" tools

__Moderate Capabilities (Hackers)__
* Generally knowledgable
* Small to moderate resources
* N-day vulnerabilities

__Highly Capable (APT/Org Crime)__
* Highly Knowledgable
* Moderate to Large resources
* N-day vulnerabilitiesand 0-day access

__Apex Predators (Nation States)__
* Highly Knowledgable
* Exceptional access to resources
* N-day vulnerabilities and 0-day access

`Insider Threat` - is a malicious actor that operates with intentional
privilege that would otherwise be inaccessible

`Social Engineering Attacks` - aim to exploit human(s) in order to gain or
improve access to the target systems

`Defenses in Depth` - a way to construct security protections in which one
can fail but others are still operational

# Cryptography
Cryptography is an extremely formal part of secuirty, extremely well studied,
a geat tool when appropriate, lots of fun to use and break.

Cryptography is not a solution to all problems, not reliable UNLESS implemented
and used correctly, something you should never use yourself.

__Properties of a Secure Channel__
* Confidentiality
- Messages can't be read by 3rd party
* Message Integrity
- Messages can't be unknowingly modified
* Sender Authenticity
 -Messages can't be created by non-1st party
	
`Hash Function`
* Input - arbitrary length data
* Output - Fixed length digest
* Attributes - Publicly known function && no key or secret used in construction
			 
__Needed Security Properties__ 
* Collision resistance
- hard to find x and x' such that H(x) == H(x')
* Preimage resistance
- Can't construct x given H(x)
* Second preimage resistance
- Given x it's hard to find x' such that H(x) == H(x')

__Common Hash Functions__
* MD5 - Trivial to collide, known use by attackers, DO NOT USE
* SHA1 - Can collide with effort, DO NOT use in NEW systems

Most hash functions use the __Merkle-Damgard contruction__ which uses fixed length
blocks and pads on finalization. Most of these hashes are vulnerable to _length-extension_
attacks. 

__Hash Collision__
* Arbitrary collisions
* Chosen-prefix collision

`HMAC` - is a Hash-based Message Authentication Code that ensure

`Random Number Generator` - HARD
`/dev/random` - very "close to random"
`/dev/urandom` - is "usually random"

__One-Time Pad__
Extremely simple to use, fast, and provably secure
Almost impossible to use in the real-world due to key reuse leaks plaintext

__Stream Cipher__
* "Infinite Length one-time pad"
* Shared key known by all participants
* Key is "expanded ...

__RC4 Stream Cipher__
* originally a "trade secret"
* extremely fast
* biased output at the beginning

__Block Cipher__
* Fixed-size input
* Fixed-size output
* Substitutions from secret state
- "s-boxes"

__Cipher Modes__ 
Block ciphers tak fixed-length inputs, input data

`Electronic Codebook Mode (ECB)` - each block of plaintext fed through ciphers,
pad last block to correct length

`Counter Mode (CTR)` - "initialization vector (IV)" used to differentiate blocks
(increments) 

`Cipher Block Chaining (CBC)` - IV is the previous block's output, assume no repeats,
pad last block _Padding Oracle Attacks_

`Galois/Counter Mode` - CTR + built-in authentication

`Public Key Cryptography` - a family of cryptosystems that leverage key pairs to perform
asymmetric crytographic operations

__RSA Key Generation__
_P_ = 61
_Q_ = 53
_N_ = P \* Q = 3233
_E_ = 17
E \* D = 1 mod LCM(P - 1, Q - 1)
Public Key = (E, N)
Private Key = (D, N)

__Attacking RSA__
An actor who can recover P and Q from N can recreate the private key. Examples:
* Poor randomness
* insufficient key sizes 
* computation over-match
* vulnerable creation tactic

`Eliptic Curve Cryptography`
`y**2 = x**3 + ax + b`
`a` and `b` are defined by the chosen curve

# HTTPS/TLS
`TLS protocol` - used to protect most of the common Internet protocols
* HTTP -> HTTPS
* FTP -> FTPS
* SMTP -> SMTPS
* Some VPNs
* SSH uses its own thing

TLS provides generic secure channel with very little overhead
## The network is evil
* Government surveillance
* ISP tracking / ad injection
* Compromised Wi-Fi routers

TLS protocol Characteristics  
* content agnostic
* one or both endpoints can be authenticated
* well-studied and iteratively improved
   - SSL v1,v2,v3
   - TSL v1.0, 1.1, 1.2, 1.3

Parameter Negotiation  
__GOAL__: Determine how endpoints will communicate
* Symmetric cipher
* ...

TLS Client-Write Key Exchange  
Client generates random secret. Encrypts to server's public key,
server decrypts to recover shared secret. __Removed in TLS v1.3__

Forward Secrecy - the property that traffic can not be decrypted

__Diffie-Hellman Key Exchange__  
Finite-Field Diffie Hellman:    
* Create/agree on a "safe prime" _P_
`p = 2p' + 1`
* create/agree on a "generator" g 
* keyshares _g**a_ and _g**b_
   - _a_ and _b_ are never shared
* shared secret: `g**ab`

__Small Subgroup Attack__  
subgroup sizes are dependan on factors of `p-1`
* _p = 19_ :: `1,2,3,6,9,18`
* generator chosen

Authentication and Verification  
__GOAL__: Ensure that
* endpoints are who they claim to be
* both endpoints saw the same transcript  

Client authentication is optional in TLS 

__TLS 1.3__
~100ms latency
single round-trip required by default, and may require additional. Able
to create connection and pass content with zero round-trips
* 0RTT

HTTPS Upgrade  
3XX HTTP redirects are used to send users to HTTPS
* 301 is permanent
* 302 is temporary

Vulnerable to "SSL stripping" attacks. Can only upgrade single page at a
time. 

Mixed Content  
Main page is HTTPS but some resources are HTTP, which is blocked by most
browsers. Cookies set inside HTTPS can be leaked over HTTP, but depends
on cookie parameters. 

HSTS  
HTTP Strict Transport Security. More generic version of the 3XX redirect.
Can be preloaded into browsers. 

Certificate Transparency - when certs are issued, they are posted to a public
ledger (browsers require inclusion in multiple DBs). Allows real-time and
historical monitoring.

# HTTPS/TLS Attacks
__Exploit the User__  
Phishing - cloned version of a legitimate site for cred grabbing
Homograph Attack - website whose URL is meant to fool users into believing it's
   someone else
Punycode - a way to encode Unicode characters as ascii-only characters
	`prufung --> xn--prfung-4ya`
Internationalized Domain Names (IDNs) - domain names that ...

__Exploit the Implementation__  
SSL Stripping - active MitM relays content between client and server. Client
   sees HTTP, and server sees HTTPS
Fooling CA Validation - attacker acquires a valid SSL cert via trickery of the CA
Null Ciphersuites - 21 defined by IANA. Explicitly do not encrypt content. Zero-
   value is effectively "make TCP more expensive"
Implementation Bug - Heartbleed, Goto Fail, Null Prefix Attack, BERsek, 2020 SChannel Vuln
Crime/Breach - induce browser to request crafted URLs, compression output may be longer/
   shorter based on input, ciphertext length leaks info
Padding Oracle - an implementation which leaks sensitive information to an attacker by
   indicating whether the padding is correct or not
Bleichenbacher Attack - Relies on PKCS#1 
Export Cryptography - Limited to 64 bit symmetric keys, 512 bit RSA/DH. Most restrictions
   removed by 2000

__Exploit the Crypto__  


# Evolutionary Computing Approaches for National Security Problems
Many computational problems can be formulated as __generate-and-test__ search problems. A
__search space__ contains the set of all possible solutions. A __search space generator__ is 
_complete_ if it can generate the entire search space. An __objective function__ tests the 
quality of a solution. A __heuristic__ is a problem-dependent rule-of-thumb. A __meta-heuristic__
determines the sampling order over a search space with the goal to find a near-optimal solution
(or set of solutions). A __hyper-heuristic__ is a meta-heuristic for a space of programs.
A __Black-Box Search Algorithm (BBSA)__ is a meta-heuristic which iteratively generates trial
solutions employing solely the information gained from previous trial solutions, but no problem
knowledge. __Evolutionary Algorithms__ can be described as a class of stochastic, population based
BBSAs inspired by Evolution Theory, Genetics, and Population Dynamics. __Genetic Programming__
is a type of EA for searching a space of programs.

# Hardware + Security
* Trusted Computing Base - all of the things that must be working correctly for the software to
  run as expected
  