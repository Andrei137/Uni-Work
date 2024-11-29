import { GraphQLBoolean } from 'graphql';
import userInputType from '../types/userInputType.js';
import { createEntity } from '../../fakeDb.js';

const createUserMutationResolver = (_, args, context) => {
  const isAuthorized = !!context.user_id;
  if (isAuthorized) {
    createEntity('users', args.user);
    return true;
  }
  return false;
};

const createUserMutation = {
  type: GraphQLBoolean,
  args: {
    user: { type: userInputType }
  },
  resolve: createUserMutationResolver
};

export default createUserMutation;
