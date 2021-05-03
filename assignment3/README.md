# Assignment 3
## Members
Daniel Kim

Heng Jerry Quan
## Questions
### SQLi
The SQL Injection page contains a box which a user can use to submit a query to search for a user's name in the database.

To get a list of all users in the database, we inserted the command `*' or '1' = '1`. This works because the input is not sanitized on the server side. The original SQL query looks something like:
```
SELECT *
FROM users
WHERE id = '$input'
```
Because the input is not sanitized, the query ends up looking something like this:

```
SELECT *
FROM users
WHERE id = '*' or '1' = '1'
```
Since the `'1' = '1'` is always true, this command will fetch all users in the table and return them to the attacker.

After changing the security level to medium, this kind of attack no longer works because the text box has been replaced with a drop down list. This way, the only available options are the provided options.

### Reflected XSS
The reflected XSS pages has a text box that takes a string ($user) and will reflect "Hello $user" on the page.

To perform a reflected XSS attack, we can enter javascript code instead of an ordinary string. We chose to enter `<script>alert("reflected XSS test")</script>`. When this text is reflected, it will instead pop up an alert, but one can easily switch this out for something more malicious.

After increasing the security level to medium, the server side removes the <script> tag, preventing the javascript from being interpretted as code. This simple kind of reflected XSS will not work on medium level security DVWA.
