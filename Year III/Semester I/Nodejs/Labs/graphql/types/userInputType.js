import { GraphQLInputObjectType, GraphQLString } from 'graphql'

const userInputType = new GraphQLInputObjectType({
  name: 'UserInput',
  fields: {
    name: {
      type: GraphQLString,
    }
  }
});

export default userInputType;
