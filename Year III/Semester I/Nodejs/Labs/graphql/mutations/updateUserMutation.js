import { GraphQLInt } from 'graphql';
import userInputType from '../types/userInputType.js';
import { findEntity, updateEntity } from '../../fakeDb.js';
import userType from '../types/userType.js';

const updateUserMutationResolver = (_, args) => {
  const { id, user } = args;
  updateEntity('users', id, user);
  return findEntity('users', id);
};

const updateUserMutation = {
  type: userType,
  args: {
    user: { type: userInputType },
    id: { type: GraphQLInt }
  },
  resolve: updateUserMutationResolver
};

export default updateUserMutation;
