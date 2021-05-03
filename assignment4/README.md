# Assignment 4
## Members
Daniel Kim

Heng Jerry Quan

### Stored XSS attack
The stored XSS attack page stores a guest book where users may leave their name and a message.

We can perform a stored XSS attack by leaving `<script>alert("NEVER GONNA GIVE YOU UP")</script>` in the message field (the username field is too short). When the page tries to render the message we left, it interprets the script tag as being part of the native code and renders the script, triggering an alert. This script will be triggered every time the message is loaded (i.e. every time the page is loaded).

On a medium security level, the message was sanitized on the server side and the `<script></script>` tags were removed, leaving only `alert("NEVER GONNA GIVE YOU UP)` in the message.

### Comparing Low and High security
We looked at the code for both low and high security. Looking at the source code, the html is basically the same, except one of the loaded php files. The low security page will load the php file at `localhost/vulnerabilities/view_source.php?id=xss_s&security=low` while high security loads `localhost/vulnerabilities/view_source.php?id=xss_s&security=high` instead.

Comparing the two, we see that both security levels sanitize their inputs. However, at low security, the only sanitization done is the removal of all forward slash (\\) characters using `stripslashes`. Meanwhile, the high level security code looks specifically for <script> tags and replaces them with an empty string "". This change is effective because removing forward slashes still allows an attacker to store javascript code. With the <script> tags stripped however, an attacker's javascript will effectively be the same as plaintext.
