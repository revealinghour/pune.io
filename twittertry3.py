import twitter
api = twitter.Api()

statuses=api.GetPublicTimeline()
print [s.user.name for s in statuses]
