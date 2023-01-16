### Branch Conventions

**Disclaimer - Always create a new temporary branch before development. DO NOT WORK OFF FROM dev or main branch**

### **main** branch 🚀 

Production Ready code. Need to keep the master branch stable and updated. Merging is possible only after code review.

### **dev** branch ‍💻 (Not applicable for current project. See main ^)

Staging code. Ready for testing.
To merge to dev, please create PR. dev branch undergo reviews and tests before merging into main branch.

### **test** branch 🧪

QA and test. Ensure a stable codebase for the production environment through the QA testing process.

### **temporary** branch ⏳

- wip - Works in progress; stuff I know won't be finished soon
- feat - Feature I'm adding or expanding
- bug - Bug fix or experiment
- junk - Throwaway branch created to experiment

#### Examples

```
feat/login
bug/create-user-page-validation-issue
```

### References 📄

- https://hackernoon.com/git-branch-naming-convention-7-best-practices-to-follow-1c2l33g2


### Commit Conventions

### Type of commits 🤖

- **feat/✨**: The new feature you're adding to a particular application
- **fix/🐛**: A bug fix
- **style/💄**: Feature and updates related to styling
- **refactor/♻️**: Refactoring a specific section of the codebase
- **test/✅**: Everything related to testing
- **docs/📝**: Everything related to documentation
- **chore**: Regular code maintenance.[ You can also use emojis to represent commit types]

### Other Conventions 👾

- Capitalized, short (50 chars or less) summary
- Remove unnecessary punctuation marks
- Do not end the subject line with a period

### Examples ✍️

```sh
# bad practices 👎
# keep commit less than 50 words
git commit -m "feat: Created login page that uses hooks for validation, and some more stuff making this message too long"

# remove unnecessary punctuation marks
git commit -m "feat: Integrated AWS into app!"

# missing type of commit
git commit -m "Fix and created admin page"

# good practices 👍
git commit -m "feat: Created login page"

git commit -m "fix: Fix issue with otp input validation"

git commit -m "refactor: Make form input modular"

git commit -m "📝: Added setup to readme:
```

### References 🏡

- https://gitmoji.dev/
- https://www.freecodecamp.org/news/writing-good-commit-messages-a-practical-guide/
- https://commitizen-tools.github.io/commitizen/


### PR Conventions

**Remember to wait for someone to approve your PR before merging.**

## Format 💽

Below are the format for PR subject and description.

### **Subject ✍️**

- Short and descriptive summary
- Start with corresponding ticket/story id (e.g. from Jira, GitHub issue, etc.)
- Should be capitalized and written in imperative present tense
- Not end with period

**#[Ticket_ID] PR description**

#### **Examples**

```
#33 Create add new opportunity page
#34 #35 Added login and register features
```

### **Description 📝**

- Separated with a blank line from the subject
- Explain what, why, etc.
- Max 72 chars or short and simple yet understandable.
- Each paragraph capitalized

#### **Examples**

```
This pull request is part of the work to make it easier for people to contribute to naming convention guides. One of the easiest way to make small changes would be using the Edit on Github button.

To achieve this, we needed to:
- Find the best Gitbook plugin which can do the work
- Integrate it in all the pages to redirect the user to the right page on GitHub for editing
- Make it visible on the page so users can notice it easily
```

## Linking of issues/stories to PR 🔗

If the branch is linked to stories project boards, remember to add them to the PR description and development. This will help to track the progress of the stories.

### **Examples**

Refer to image below.
![PR linking to stories](../git/assets/git_pr_convention.png)

## Assign a reviewer 🙍

To merge a PR, you need to assign a reviewer. The reviewer will review the code and approve the PR. Once approved, you can merge the PR.
**You can assign your project manager or team leader as the reviewer. Different for different projects.**

## References 🏡

- https://namingconvention.org/git/pull-request-naming.html