import { GraphQLInt, GraphQLString, GraphQLObjectType } from 'graphql';

const userType = new GraphQLObjectType({
  name: "User",
  fields: {
    id: {
      type: GraphQLInt,
    },
    name: {
      type: GraphQLString,
    }
  }
});

export default userType;
