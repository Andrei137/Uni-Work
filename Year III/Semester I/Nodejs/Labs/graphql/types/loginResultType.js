import {
  GraphQLObjectType,
  GraphQLString,
  GraphQLNonNull
} from 'graphql'

const loginResultType = new GraphQLObjectType({
  name: 'LoginResult',
  fields: {
    token: { type: new GraphQLNonNull(GraphQLString) },
  }
});

export default loginResultType;
