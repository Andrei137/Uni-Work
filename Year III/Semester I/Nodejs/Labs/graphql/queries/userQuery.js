import { GraphQLInt } from 'graphql';
import userType from '../types/userType.js';
import { findEntity } from '../../fakeDb.js';

const userQueryResolver = (_, { id }) => findEntity('users', id);

const userQuery = {
  type: userType,
  args: {
    id: { type: GraphQLInt }
  },
  resolve: userQueryResolver
};

export default userQuery;
