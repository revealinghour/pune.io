import twitter
api = twitter.Api()

input=raw_input('Enter user name ')
statuses = api.GetUserTimeline(input)
print [s.text for s in statuses]
