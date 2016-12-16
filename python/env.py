def cfg():
  return {
    'tokenurl': 'https://abc.com/auth/oauth2/token/',
    'userurl': 'https://abc.com/auth/api/users/{0}/exists/',
    'userlisturl': 'https://abc.com/auth/api/users/',
    'client': {
      'id': 'client id',
      'secret': 'client secret'
    },
    'user': {
      'id': 'user id',
      'secret': 'user secret'
    },
    'scope': 'User'
  }
